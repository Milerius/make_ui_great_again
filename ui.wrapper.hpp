//
// Created by Roman Szterg on 18/12/2019.
//

#ifndef UI_WORKFLOW_UI_WRAPPER_HPP
#define UI_WORKFLOW_UI_WRAPPER_HPP

// C System Headers
#include <cstddef>
#include <stdint.h>
#include <unordered_map>

class timer
{
  public:
    // Initializes variables
    timer();

    // The various clock actions
    void start();

    void stop();

    void pause();

    void unpause();

    // Gets the timer's time
    uint32_t getTicks();

    // Checks the status of the timer
    bool isStarted();

    bool isPaused();

  private:
    // The clock time when the timer started
    uint32_t m_start_ticks;

    // The ticks stored when the timer was paused
    uint32_t m_paused_ticks;

    // The timer status
    bool m_paused;
    bool m_started;
};

struct opengl_image
{
    unsigned int id;
    int          width;
    int          height;
};

class antara_gui
{
    bool                                          m_first_font{false};
    void*                                         m_gl_context;
    timer                                         m_timer;
    bool                                          m_close{false};
    int                                           m_fps_cap{30};
    void                                          render();
    std::unordered_map<const char*, opengl_image> m_images;

  public:
    antara_gui(const char* title, std::size_t width = 1ull, std::size_t height = 1ull);
    ~antara_gui() noexcept;
    bool is_close() const;
    void set_close(bool close);
    void show_demo();
    void pre_update() noexcept;
    void update() noexcept;
    void load_font(const char* path, float size_pixels = 15.f) noexcept;
    void load_awesome_font(const char* path, float size_pixels = 15.f) noexcept;
    bool load_image(const char* id, const char*path, opengl_image& img);
    opengl_image& get_image(const char* id);
};

#endif // UI_WORKFLOW_UI_WRAPPER_HPP
