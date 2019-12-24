//
// Created by Roman Szterg on 18/12/2019.
//

#include <cstdlib>

//! Project Headers
#include "ui.wrapper.hpp"

//! C++ System Headers
#include <iostream>

//! Dependencies Headers
#include <IconsFontAwesome5.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef _WIN32

#    include <imgui_impl_win32.h>

#endif



SDL_Window* m_window;

antara_gui::antara_gui(const char* title, std::size_t width, std::size_t height)
{
#if _WIN32
    ImGui_ImplWin32_EnableDpiAwareness();
#endif
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        std::exit(1);
    }


#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#elif __linux__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
    m_window          = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
    assert(m_window);
    m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    bool err = gladLoadGL() == 0;
    assert(!err);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    io.ConfigViewportsNoAutoMerge     = true;
    io.ConfigViewportsNoDefaultParent = true;
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

antara_gui::~antara_gui() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(m_gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void
antara_gui::update() noexcept
{
    render();
    // If frame finished early
    int frame_ticks = m_timer.getTicks();
    int fps_cap_ms  = 1000 / m_fps_cap;
    if (frame_ticks < fps_cap_ms)
    {
        // Wait remaining time
        SDL_Delay(fps_cap_ms - frame_ticks);
    }

    // Start cap timer
    m_timer.start();
}

void
antara_gui::render()
{
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window*   backup_current_window  = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        SDL_HideWindow(backup_current_window);
    }

    SDL_GL_SwapWindow(m_window);
}
void
antara_gui::pre_update() noexcept
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) m_close = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window)) m_close = true;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();
}

bool
antara_gui::is_close() const
{
    return m_close;
}
void
antara_gui::set_close(bool close)
{
    m_close = close;
}

void
antara_gui::show_demo()
{
    static bool open = true;
    ImGui::ShowDemoWindow(&open);
    if (not open) m_close = true;
}

void
antara_gui::load_font(const char* path, float size_pixels) noexcept
{
    auto im_gui_io = ImGui::GetIO();

    if (not m_first_font)
    {
        im_gui_io.Fonts->Clear();
        m_first_font = true;
    }

    im_gui_io.Fonts->AddFontFromFileTTF(path, size_pixels);
}
void
antara_gui::load_awesome_font(const char* path, float size_pixels) noexcept
{
    static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    ImFontConfig         icons_config;
    auto                 im_gui_io = ImGui::GetIO();
    icons_config.MergeMode         = true;
    icons_config.PixelSnapH        = true;

    if (not m_first_font)
    {
        im_gui_io.Fonts->Clear();
        m_first_font = true;
    }

    im_gui_io.Fonts->AddFontFromFileTTF(path, size_pixels, &icons_config, icons_ranges);
}

timer::timer()
{
    // Initialize the variables
    m_start_ticks  = 0;
    m_paused_ticks = 0;

    m_paused  = false;
    m_started = false;
}

void
timer::start()
{
    // Start the timer
    m_started = true;

    // Unpause the timer
    m_paused = false;

    // Get the current clock time
    m_start_ticks  = SDL_GetTicks();
    m_paused_ticks = 0;
}

void
timer::stop()
{
    // Stop the timer
    m_started = false;

    // Unpause the timer
    m_paused = false;

    // Clear tick variables
    m_start_ticks  = 0;
    m_paused_ticks = 0;
}

void
timer::pause()
{
    // If the timer is running and isn't already paused
    if (m_started && !m_paused)
    {
        // Pause the timer
        m_paused = true;

        // Calculate the paused ticks
        m_paused_ticks = SDL_GetTicks() - m_start_ticks;
        m_start_ticks  = 0;
    }
}

void
timer::unpause()
{
    // If the timer is running and paused
    if (m_started && m_paused)
    {
        // Unpause the timer
        m_paused = false;

        // Reset the starting ticks
        m_start_ticks = SDL_GetTicks() - m_paused_ticks;

        // Reset the paused ticks
        m_paused_ticks = 0;
    }
}

uint32_t
timer::getTicks()
{
    // The actual timer time
    Uint32 time = 0;

    // If the timer is running
    if (m_started)
    {
        // If the timer is paused
        if (m_paused)
        {
            // Return the number of ticks when the timer was paused
            time = m_paused_ticks;
        }
        else
        {
            // Return the current time minus the start time
            time = SDL_GetTicks() - m_start_ticks;
        }
    }

    return time;
}

bool
timer::isStarted()
{
    // Timer is running and paused or unpaused
    return m_started;
}

bool
timer::isPaused()
{
    // Timer is running and paused
    return m_paused && m_started;
}

bool
LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int            image_width  = 0;
    int            image_height = 0;
    unsigned char* image_data   = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width   = image_width;
    *out_height  = image_height;

    return true;
}

bool
antara_gui::load_image(const char* id, const char* path, opengl_image& image)
{
    auto res = LoadTextureFromFile(path, &image.id, &image.width, &image.height);
    if (res) { m_images[id] = image; }
    return res;
}

opengl_image&
antara_gui::get_image(const char* id)
{
    return m_images.at(id);
}
bool
antara_gui::load_image(const char* path, opengl_image& img)
{
   return LoadTextureFromFile(path, &img.id, &img.width, &img.height);
}
