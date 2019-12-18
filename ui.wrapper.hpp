//
// Created by Roman Szterg on 18/12/2019.
//

#ifndef UI_WORKFLOW_UI_WRAPPER_HPP
#define UI_WORKFLOW_UI_WRAPPER_HPP

// C System Headers
#include <stdint.h>
#include <cstddef>

class timer
{
  public:
    // Initializes variables
    timer();

    // The various clock actions
    void
    start();

    void
    stop();

    void
    pause();

    void
    unpause();

    // Gets the timer's time
    uint32_t
    getTicks();

    // Checks the status of the timer
    bool
    isStarted();

    bool
    isPaused();

  private:
    // The clock time when the timer started
    uint32_t m_start_ticks;

    // The ticks stored when the timer was paused
    uint32_t m_paused_ticks;

    // The timer status
    bool m_paused;
    bool m_started;
};

class antara_gui
{
    void*         m_gl_context;
    timer         m_timer;
    bool          m_close{false};
    int           m_fps_cap{30};
    void          render();

  public:
    antara_gui(const char* title, std::size_t width = 1ull, std::size_t height = 1ull);
    ~antara_gui() noexcept;
    bool is_close() const;
    void set_close(bool close);
    void show_demo();
    void pre_update() noexcept;
    void update() noexcept;
};

#endif // UI_WORKFLOW_UI_WRAPPER_HPP
