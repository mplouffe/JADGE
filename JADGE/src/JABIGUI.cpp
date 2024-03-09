#include "JABIGUI.h"

JABIGUI::JABIGUI() :
    io(ImGui::GetIO())
{ 
    (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

JABIGUI::JABIGUI(JABIGUI* other) :
    io(other->io)
{ }

JABIGUI::~JABIGUI()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void JABIGUI::init(SDL_Window* window, SDL_Renderer* renderer)
{
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
}

void JABIGUI::render()
{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		
		ImGui::NewFrame();
		ImGui::Begin("J_A_D_G_E");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("Hello World! It's ya boy... JA_BIGE!!! \\O.o/");
		ImGui::End();

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Checkbox", &checkbox_demo);      // Edit bools storing our window open/close state

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))
		{
			counter++;
		}                           // Buttons return true when clicked (most widgets return true when edited/activated)

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Render();
}