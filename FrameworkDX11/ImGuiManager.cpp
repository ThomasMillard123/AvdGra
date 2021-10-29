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
            ImGui::InputFloat("X", &data.Material.Diffuse.x);
            ImGui::InputFloat("Y", &data.Material.Diffuse.y);
            ImGui::InputFloat("Z", &data.Material.Diffuse.z);


            ImGui::Text("Specular");
            ImGui::InputFloat("sX", &data.Material.Specular.x);
            ImGui::InputFloat("sY", &data.Material.Specular.y);
            ImGui::InputFloat("sZ", &data.Material.Specular.z);
            ImGui::InputFloat("power", &data.Material.SpecularPower);

            GameObject->GetAppearance()->SetMaterial(data);
        }


    }
    ImGui::End();
}

static float pos2[] = {0.0f,0.0f,0.0f};
static float Dir[] = { 0.0f,0.0f,0.0f };
static float Colour[] = { 0.0f,0.0f,0.0f,0.0f };
static float attenuation[] = { 0.0f,0.0f,0.0f };
static const char* current_item1 = NULL;
static string name1;
static bool enable;
static bool Load2 = false;
void ImGuiManager::LightControl(LightControll* LightControl)
{

    if (!Load2) {
        name1 = LightControl->GetLight(0)->GetName();
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

                        

                        current_item1 = name1.c_str();
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)

                    }

                }
                ImGui::EndCombo();
            }

            pos2[0] = LightControl->GetLight(name1)->GetLightData().Position.x;
            pos2[1] = LightControl->GetLight(name1)->GetLightData().Position.y;
            pos2[2] = LightControl->GetLight(name1)->GetLightData().Position.z;


            Dir[0] = LightControl->GetLight(name1)->GetLightData().Direction.x;
            Dir[1] = LightControl->GetLight(name1)->GetLightData().Direction.y;
            Dir[2] = LightControl->GetLight(name1)->GetLightData().Direction.z;

            Colour[0] = LightControl->GetLight(name1)->GetLightData().Color.x;
            Colour[1] = LightControl->GetLight(name1)->GetLightData().Color.y;
            Colour[2] = LightControl->GetLight(name1)->GetLightData().Color.z;
            Colour[3] = LightControl->GetLight(name1)->GetLightData().Color.w;


            attenuation[0] = LightControl->GetLight(name1)->GetLightData().ConstantAttenuation;
            attenuation[1] = LightControl->GetLight(name1)->GetLightData().LinearAttenuation;
            attenuation[2] = LightControl->GetLight(name1)->GetLightData().QuadraticAttenuation;

            ImGui::Text("Position");
            ImGui::InputFloat("X", &pos2[0]);
            ImGui::InputFloat("Y", &pos2[1]);
            ImGui::InputFloat("Z", &pos2[2]);

            LightControl->GetLight(name1)->setPos(XMFLOAT4(pos2[0], pos2[1], pos2[2], 0.0f));


            enable = LightControl->GetLight(name1)->GetLightData().Enabled;
            ImGui::Checkbox("Enabled", &enable);
            LightControl->GetLight(name1)->SetEnabled(enable);


           
            ImGui::SliderFloat4("Colour (R,G,B,A)", Colour, 0, 1);
            LightControl->GetLight(name1)->setColour(XMFLOAT4(Colour[0], Colour[1], Colour[2], Colour[3]));

             if (LightControl->GetLight(name1)->GetLightData().LightType == LightType::DirectionalLight) {
                ImGui::Text("Direction");
                ImGui::InputFloat("A", &Dir[0]);
                ImGui::InputFloat("B", &Dir[1]);
                ImGui::InputFloat("C", &Dir[2]);

                LightControl->GetLight(name1)->setDirection(XMFLOAT4(Dir[0], Dir[1], Dir[2], 0.0f));
              }


            if (LightControl->GetLight(name1)->GetLightData().LightType == LightType::PointLight || LightControl->GetLight(name1)->GetLightData().LightType == LightType::SpotLight) {
                ImGui::Text("attenuation");
                ImGui::SliderFloat("Constant", &attenuation[0], 1.0f, 10.0f, "%.2f");
                ImGui::SliderFloat("Linear", &attenuation[1], 0.0f, 5.0f, "%.4f");
                ImGui::SliderFloat("Quadratic", &attenuation[2], 0.0f, 2.0f, "%.7f");


                LightControl->GetLight(name1)->SetAttenuation(attenuation[0], attenuation[1], attenuation[2]);
            }

            if (ImGui::Button("Reset")) {

              
            }

        }
        if (ImGui::CollapsingHeader("Add Light"))
        {

             float posNew[] = { 0.0f,0.0f,0.0f };
             float DirNew[] = { 0.0f,0.0f,0.0f };
             float ColourNew[] = { 0.0f,0.0f,0.0f,0.0f };
             float attenuationNew[] = { 0.0f,0.0f,0.0f };
             string Name;
             float Ang=0;
             bool On;


             ImGui::Text("Name");
             ImGui::InputText("Name",&Name);

             ImGui::Text("Enabled");
             ImGui::Checkbox("Enabled", &On);

             ImGui::Text("Light Type");



            ImGui::Text("Position");
            ImGui::InputFloat("X", &posNew[0]);
            ImGui::InputFloat("Y", &posNew[1]);
            ImGui::InputFloat("Z", &posNew[2]);


            ImGui::Text("Direction");
            ImGui::InputFloat("A", &DirNew[0]);
            ImGui::InputFloat("B", &DirNew[1]);
            ImGui::InputFloat("C", &DirNew[2]);

            
            ImGui::Text("Angle");
            ImGui::InputFloat("Angle", &Ang);

            ImGui::Text("Colour");
            ImGui::InputFloat("A", &ColourNew[0]);
            ImGui::InputFloat("B", &ColourNew[1]);
            ImGui::InputFloat("C", &ColourNew[2]);
            ImGui::InputFloat("C", &ColourNew[2]);

            ImGui::Text("attenuation");
            ImGui::SliderFloat("Constant", &attenuationNew[0], 0, 10);
            ImGui::SliderFloat("Linear", &attenuationNew[1], 0, 5);
            ImGui::SliderFloat("Quadratic", &attenuationNew[2], 0, 1);
            


            if (ImGui::Button("add")) {
                
                
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