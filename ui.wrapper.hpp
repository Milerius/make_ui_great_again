//
// Created by Roman Szterg on 18/12/2019.
//

#ifndef UI_WORKFLOW_UI_WRAPPER_HPP
#define UI_WORKFLOW_UI_WRAPPER_HPP

// C System Headers
#include <cstddef>

//! Dependencies Headers
#include <SDL2/SDL.h>

class timer
{
  public:
    // Initializes variables
    timer()
    {
        // Initialize the variables
        m_start_ticks  = 0;
        m_paused_ticks = 0;

        m_paused  = false;
        m_started = false;
    }

    // The various clock actions
    void
    start()
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
    stop()
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
    pause()
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
    unpause()
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

    // Gets the timer's time
    Uint32
    getTicks()
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

    // Checks the status of the timer
    bool
    isStarted()
    {
        // Timer is running and paused or unpaused
        return m_started;
    }

    bool
    isPaused()
    {
        // Timer is running and paused
        return m_paused && m_started;
    }

  private:
    // The clock time when the timer started
    Uint32 m_start_ticks;

    // The ticks stored when the timer was paused
    Uint32 m_paused_ticks;

    // The timer status
    bool m_paused;
    bool m_started;
};

class antara_gui
{
    SDL_Window*   m_window;
    SDL_GLContext m_gl_context;
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
