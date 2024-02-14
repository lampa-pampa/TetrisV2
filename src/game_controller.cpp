#include "game_controller.h"
#include "game.h"
#include "game_state.h"

GameController::GameController(
        std::unique_ptr<InputReceiver> &&input_receiver,
        std::unique_ptr<Timer> &&timer,
        std::unique_ptr<Game> &&game)
:
    input_receiver(std::move(input_receiver)),
    timer(std::move(timer)),
    game(std::move(game))
{
    input_receiver->connect_move_left_pressed([&game]()->void{game->move_left();});
    input_receiver->connect_move_right_pressed([&game]()->void{game->move_right();});
    input_receiver->connect_rotate_pressed([&game]()->void{game->rotate();});
    input_receiver->connect_soft_drop_pressed([&game]()->void{game->soft_drop();});
    input_receiver->connect_hard_drop_pressed([&game]()->void{game->hard_drop();});
    input_receiver->connect_hold_pressed([&game]()->void{game->hold_pressed();});
    input_receiver->connect_pause_pressed([this]()->void{this->on_pause_pressed();});
}

void GameController::on_pause_pressed()
{
    switch (game->get_state())
    {
        case GameState::in_progress:
            timer->stop();
            game->set_state(GameState::paused);
        break;
        case GameState::paused:
            timer->start();
            game->set_state(GameState::in_progress);
        break;
        default:
        break;
    }
}