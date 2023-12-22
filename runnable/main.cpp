#include <core_sdk/logger.hpp>
#include <core_sdk/singleton.hpp>

#include <core_sdk/macros/memory_macros.hpp>
#include <core_sdk/macros/string_macros.hpp>

#include <core_sdk/math/math.hpp>
#include <core_sdk/scripts/file_to_hex.hpp>

#include <core_sdk/types/point/point2D.hpp>
#include <core_sdk/types/point/point3D.hpp>
#include <core_sdk/types/point/point4D.hpp>

#include <core_sdk/types/vector/vector3D.hpp>
#include <core_sdk/types/vector/vector2D.hpp>

#include <core_sdk/types/color.hpp>
#include <lib_gui/lib_gui.hpp>
#include <lib_gui/interface/ui_drag_bar.hpp>
#include <lib_gui/interface/ui_form.hpp>

#include <lib_hashing/crc32.hpp>
#include <lib_hashing/fnv1a.hpp>
#include <lib_hashing/md5.hpp>

#include <lib_json_config/lib_json_config.hpp>

#include <lib_threading/async_caller/async_caller.hpp>
#include <lib_threading/signal_handler.hpp>
#include <lib_threading/thread_pool/thread_pool.hpp>
#include <lib_threading/timer/timer.hpp>
#include <lib_threading/tripple_buffer.hpp>
#include <lib_utils/fps_helper.hpp>

#include <lib_window_creation/lib_window_creation.hpp>

#include "font.hpp"

class test_c
{
public:

private:
};

int main()
{
    static test_c c1{};
    static test_c c2{};
    static test_c c3{};

    static lib::threading::triple_buffer<test_c> buffers{ c1, c2, c3 };

    const auto pool = std::make_shared<lib::threading::thread_pool>(10);
    const auto caller = std::make_shared<lib::threading::async_caller>();
    const auto signal = std::make_shared<lib::threading::signal_handler<const test_c&, int>>();

    signal->register_callback([](const test_c& ignore, int val){ lib_log_i("{}", val); });
    signal->register_callback([](const test_c& ignore, int val){ lib_log_i("{}", val + 1); });
    signal->register_callback([](const test_c& ignore, int val){ lib_log_i("idk what im doing"); });

    signal->exec(c1, 0);
    signal->exec(c1, 1);

    const auto timer = std::make_unique<lib::threading::timer>(
        *caller,
        [](){ lib_log_i("oneshot timer"); },
        lib::threading::timer_mode_e::one_shot,
        std::chrono::seconds(5));

    timer->start_timer();

    const auto timer_repeating = std::make_unique<lib::threading::timer>(
        *caller,
        [](){ lib_log_i("repeating timer"); },
        lib::threading::timer_mode_e::reloading,
        std::chrono::seconds(2));

    timer_repeating->start_timer();

    caller->spawn_exec_thread();
    signal->exec(c1, 2);

    caller->add_function([](){ lib_log_i("boobs"); });
    caller->add_function([](){ lib_log_i("penis"); });
    caller->add_function([](){ lib_log_i("vagina"); });
    caller->add_function([](){ lib_log_i("sex"); });

    const auto& test_collection = std::make_shared<lib::threading::job_collection>();

    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });
    test_collection->queue_job([](){ lib_log_i("sex"); });

    const auto& test_collection2 = std::make_shared<lib::threading::job_collection>();

    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });
    test_collection2->queue_job([](){ lib_log_i("hello"); });

    pool->queue_collection(test_collection);
    pool->queue_collection(test_collection2);

    test_collection->wait_for_finish();
    test_collection2->wait_for_finish();

    lib::json_config::config_manager manager = {"./Hello", ".hello"};

    bool some_bool_1 = false;
    bool some_bool_2 = true;

    auto config_1 = std::make_shared<lib::json_config::json_config>();
    {
        config_1->add_value("hello", lib::json_config::value_type::boolean, some_bool_1);
        config_1->add_value("bye", lib::json_config::value_type::boolean, some_bool_2);
    }
    manager.register_config("hello_poo", config_1);
    manager.load_config("boos");

    // assert(some_bool_1 == false);
    // assert(some_bool_2 == false);

    const auto parameters = lib::window_creation::window_parameters_t
    {
        .window_name = "Test Window",
        .x_position = 100,
        .y_position = 100,
        .width = 1280,
        .height = 720,
        .flags = lib::window_creation::window_flag_resizeable
    };

    auto window = lib::window_creation::window_creation(parameters);
    auto fps_helper = lib::utils::fps_helper();

    const auto input = window.register_input_handler().lock();
    const auto renderer = window.register_renderer().lock();

    const auto cat_texture = renderer->add_image("../../cat.jpg");
    const auto cow_texture = renderer->add_image("../../cow.jpg");
    const auto font_texture = renderer->add_font(DroidSans, 20.f);

    lib::point2Di cursor_position = {0, 0};
    input->register_callback(lib::input::input_type::mouse, [&](const lib::input::input_callback_handler& input)
    {
        cursor_position = input.get_cursor_position();
    });

    renderer->register_callback([&](lib::rendering::render_callback_handler& render)
    {
        fps_helper.update();

        render.update_clipped_area({400, 200, 880, 520});
        render.draw_rect_filled({100, 100}, {1080, 520}, {255, 255, 255, 255});

        render.update_clipped_area({0, 0, renderer->get_window_size().x, renderer->get_window_size().y});
        render.draw_line({100, 100}, {200, 200}, {255, 0, 255, 255}, 1.f);

        render.draw_triangle({20, 50}, {50, 50}, {50, 75}, {0, 255, 0, 255}, 5.f);
        render.draw_triangle_filled({125, 500}, {140, 500}, {125, 300}, {255, 255, 255, 255});

        render.draw_image({300, 400}, {100, 100}, {255, 255, 255, 200}, cow_texture);
        render.draw_image({20, 20}, {300, 400}, {255, 255, 255, 150}, cat_texture);

        render.draw_font(
                {640, 360},
                {0, 0, 0, 255},
                font_texture,
                "hello my name jeff",
                lib::rendering::font_flags::centered_xy
            );

        render.draw_font(
                {50, 50},
                {255, 255, 255, 255},
                font_texture,
                fmt::format("min fps: {}", fps_helper.get_min_fps()),
                lib::rendering::font_flags::outline
            );

        render.draw_font(
                {50, 80},
                {255, 255, 255, 255},
                font_texture,
                fmt::format("max fps: {}", fps_helper.get_max_fps()),
                lib::rendering::font_flags::outline
            );

        render.draw_font(
                {50, 110},
                {255, 255, 255, 255},
                font_texture,
                fmt::format("avg fps: {}", fps_helper.get_average_fps()),
                lib::rendering::font_flags::outline
            );

        render.draw_font(
                {50, 140},
                {255, 255, 255, 255},
                font_texture,
                fmt::format("cur fps: {}", fps_helper.get_current_fps()),
                lib::rendering::font_flags::outline
            );

        render.draw_rect_filled(
            cursor_position - lib::point2Di{5, 5},
            {10, 10},
            {255, 255, 255, 255});
    });

    auto gui = lib::gui::gui(input, renderer);

    // build gui
    const auto some_tab = std::make_shared<lib::gui::ui_drag_bar>("Test bar");
    {

    }
    gui.register_window(some_tab);

    const auto some_tab_2 = std::make_shared<lib::gui::ui_drag_bar>("Test bar 2");
    {

    }
    gui.register_window(some_tab_2);

    const auto some_form = std::make_shared<lib::gui::ui_form>("Test window", lib::point2Di(600, 400));
    {

    }
    gui.register_window(some_form);

    const auto some_form_2 = std::make_shared<lib::gui::ui_form>("Test window 2", lib::point2Di(300, 600));
    {

    }
    gui.register_window(some_form_2);

    renderer->build_texture();
    window.run_window_loop();

    return 0;
}
