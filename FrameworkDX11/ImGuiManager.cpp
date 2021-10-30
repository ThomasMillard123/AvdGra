#include "ImGuiManager.h"
#include"DrawableGameObject.h"
#include"LightControll.h"
#include"ShaderController.h"
ImGuiManager::ImGuiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	SetBlackGoldStyle();
}

ImGuiManager::~ImGuiManager()
{
	ImGui::DestroyContext();
}

void ImGuiManager::Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* context) 
{
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(device, context);
}


void ImGuiManager::BeginRender()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::EndRender()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
static const char* current_item = NULL;
static string name;
static bool Load = false;
void ImGuiManager::DrawCamMenu(CameraController* Cams)
{
    if (!Load) {
        name =Cams->GetCurentCam()->GetCamName();
        current_item = name.c_str();
        Load = true;
    }

    if (ImGui::Begin("Cam Controls", FALSE, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::CollapsingHeader("Camera Controls"))
        {
            ImGui::Text("W                 Forward");
            ImGui::Text("A                 Left");
            ImGui::Text("S                 Backward");
            ImGui::Text("D                 Right");
            ImGui::Text("Leftmouse + move                 Look");
            ImGui::Separator();
            
        }
        if (ImGui::CollapsingHeader("Cam Select"))
        {
            
            if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
            {
                for (int n = 0; n < Cams->GetCamList().size(); n++)
                {
                    bool is_selected = (current_item == Cams->GetCamList()[n]->GetCamName().c_str()); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(Cams->GetCamList()[n]->GetCamName().c_str(), is_selected)) {

                        name = Cams->GetCamList()[n]->GetCamName();
                        Cams->SetCam(n);
                        current_item = name.c_str();
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                        
                    }
                    
                }
                ImGui::EndCombo();
            }
        }
    }
    ImGui::End();
}

static const char* current_Shader = NULL;
static string Shadername;
static bool LoadShader = false;
void ImGuiManager::ShaderMenu(ShaderController* Shader)
{
    if (!LoadShader) {
        Shadername = Shader->GetShaderData().Name;
        current_Shader = Shadername.c_str();
        LoadShader = true;
    }

    if (ImGui::Begin("Shader Controls", FALSE, ImGuiWindowFlags_AlwaysAutoResize))
    {
       
        if (ImGui::CollapsingHeader("Shader Select"))
        {

            if (ImGui::BeginCombo("##combo", current_Shader)) // The second parameter is the label previewed before opening the combo.
            {
                for (int n = 0; n < Shader->GetShaderList().size(); n++)
                {
                    bool is_selected = (current_Shader == Shader->GetShaderList()[n].Name.c_str()); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(Shader->GetShaderList()[n].Name.c_str(), is_selected)) {

                        Shadername = Shader->GetShaderList()[n].Name;
                        Shader->SetShaderData(n);
                        current_Shader = Shadername.c_str();
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

                    }

                }
                ImGui::EndCombo();
            }
        }
    }
    ImGui::End();
}



static float rotationX, rotationY , rotationZ;
static float pos[]= { 0.0f,0.0f,0.0f };
void ImGuiManager::ObjectControl(DrawableGameObject* GameObject)
{
    if (ImGui::Begin("object Controll", FALSE, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::CollapsingHeader("contolls"))
        {
            ImGui::SliderFloat("Rotation X",&rotationX,  0, 360);
            ImGui::SliderFloat("Rotation Y", &rotationY, 0, 360);
            ImGui::SliderFloat("Rotation Z", &rotationZ, 0, 360);
            GameObject->GetTransfrom()->SetRotation(rotationX, rotationY, rotationZ);


            ImGui::Text("Position");
            ImGui::InputFloat("X", &pos[0]);
            ImGui::InputFloat("Y", &pos[1]);
            ImGui::InputFloat("Z", &pos[2]);
            GameObject->GetTransfrom()->SetPosition(pos[0], pos[1], pos[2]);


            if (ImGui::Button("Reset")) {
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                pos[0] = 0.0f;
                pos[1] = 0.0f;
                pos[2] = 0.0f;
            }
        }
        if (ImGui::CollapsingHeader("Tex Controll"))
        {
 
            MaterialPropertiesConstantBuffer data= GameObject->GetAppearance()->getMaterialPropertiesConstantBuffer();
           
            bool booldata = data.Material.UseTexture;
            ImGui::Text("Texture");
            ImGui::Checkbox("On", &booldata);




            data.Material.UseTexture = booldata;

            ImGui::Text("Diffuse");
            ImGui::InputFloat("dR", &data.Material.Diffuse.x);
            ImGui::InputFloat("dG", &data.Material.Diffuse.y);
            ImGui::InputFloat("dB", &data.Material.Diffuse.z);


            ImGui::Text("Specular");
            ImGui::InputFloat("sR", &data.Material.Specular.x);
            ImGui::InputFloat("sG", &data.Material.Specular.y);
            ImGui::InputFloat("sB", &data.Material.Specular.z);
            ImGui::InputFloat("power", &data.Material.SpecularPower);

            ImGui::Text("emissive");
            ImGui::InputFloat("eR", &data.Material.Emissive.x);
            ImGui::InputFloat("eG", &data.Material.Emissive.y);
            ImGui::InputFloat("eB", &data.Material.Emissive.z);
          

            ImGui::Text("ambient");
            ImGui::InputFloat("aR", &data.Material.Ambient.x);
            ImGui::InputFloat("aG", &data.Material.Ambient.y);
            ImGui::InputFloat("aB", &data.Material.Ambient.z);
           

            GameObject->GetAppearance()->SetMaterial(data);
        }


    }
    ImGui::End();
}


static const char* current_item1 = NULL;
static string name1;
static bool Load2 = false;

static Light CurrLightData;

void ImGuiManager::LightControl(LightControll* LightControl)
{

    if (!Load2) {
        name1 = LightControl->GetLight(0)->GetName();
        CurrLightData = LightControl->GetLightList()[0]->GetLightData();
        current_item1 = name1.c_str();
        Load2 = true;
    }

    if (ImGui::Begin("Light Control", FALSE, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::CollapsingHeader("contolls"))
        {
            if (ImGui::BeginCombo("##combo", current_item1)) // The second parameter is the label previewed before opening the combo.
            {
                for (int n = 0; n < LightControl->GetLightList().size(); n++)
                {
                    bool is_selected = (current_item1 == LightControl->GetLightList()[n]->GetName().c_str()); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(LightControl->GetLightList()[n]->GetName().c_str(), is_selected)) {

                        name1 = LightControl->GetLightList()[n]->GetName().c_str();

                        
                        CurrLightData = LightControl->GetLightList()[n]->GetLightData();
                        current_item1 = name1.c_str();
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                      
                    }

                }
                ImGui::EndCombo();
            }

            CurrLightData = LightControl->GetLight(name1)->GetLightData();

            ImGui::Text("Position");
            ImGui::InputFloat("X", &CurrLightData.Position.x);
            ImGui::InputFloat("Y", &CurrLightData.Position.y);
            ImGui::InputFloat("Z", &CurrLightData.Position.z);


            bool enable = CurrLightData.Enabled;
            ImGui::Checkbox("Enabled", &enable);
            CurrLightData.Enabled = enable;

            float Colour[] = { CurrLightData.Color.x ,CurrLightData.Color.y,CurrLightData.Color.z,CurrLightData.Color.w };
            ImGui::ColorPicker4("Colour", Colour,ImGuiColorEditFlags_Float | ImGuiColorEditFlags_DisplayRGB);
            CurrLightData.Color = { Colour[0],Colour[1],Colour[2],Colour[3] };

         

            switch (LightControl->GetLight(name1)->GetLightData().LightType)
            {

            case LightType::PointLight:
                ImGui::Text("attenuation");
                ImGui::SliderFloat("Constant", &CurrLightData.ConstantAttenuation, 1.0f, 10.0f, "%.2f");
                ImGui::SliderFloat("Linear", &CurrLightData.LinearAttenuation, 0.0f, 5.0f, "%.4f");
                ImGui::SliderFloat("Quadratic", &CurrLightData.QuadraticAttenuation, 0.0f, 2.0f, "%.7f");
                break;

            case LightType::SpotLight:
            {
                ImGui::Text("attenuation");
                ImGui::SliderFloat("Constant", &CurrLightData.ConstantAttenuation, 1.0f, 10.0f, "%.2f");
                ImGui::SliderFloat("Linear", &CurrLightData.LinearAttenuation, 0.0f, 5.0f, "%.4f");
                ImGui::SliderFloat("Quadratic", &CurrLightData.QuadraticAttenuation, 0.0f, 2.0f, "%.7f");

                float SpotAngle = XMConvertToDegrees(CurrLightData.SpotAngle);
                ImGui::InputFloat("Spot Angle", &SpotAngle);
                CurrLightData.SpotAngle = XMConvertToRadians(SpotAngle);
               
            }
                break;

            case LightType::DirectionalLight:
                ImGui::Text("Direction");
                ImGui::InputFloat("A", &CurrLightData.Direction.x);
                ImGui::InputFloat("B", &CurrLightData.Direction.y);
                ImGui::InputFloat("C", &CurrLightData.Direction.z);

                
                break;

            default:
                break;
            }


            LightControl->GetLight(name1)->SetLightData(CurrLightData);

            if (ImGui::Button("Reset")) {

              
            }

        }
       
    }
    ImGui::End();
}

void ImGuiManager::SetBlackGoldStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style->FramePadding = ImVec2(4, 2);
    style->ItemSpacing = ImVec2(10, 2);
    style->IndentSpacing = 12;
    style->ScrollbarSize = 10;

    style->WindowRounding = 4;
    style->FrameRounding = 4;
    style->PopupRounding = 4;
    style->ScrollbarRounding = 6;
    style->GrabRounding = 4;
    style->TabRounding = 4;

    style->WindowTitleAlign = ImVec2(1.0f, 0.5f);
    style->WindowMenuButtonPosition = ImGuiDir_Right;

    style->DisplaySafeAreaPadding = ImVec2(4, 4);
}