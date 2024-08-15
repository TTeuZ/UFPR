import src.Constants as Constants
from src.Node import Node
from src.Game import Game
import argparse
import time

def main(args):
    node = Node(args.machine, args.port, args.neighbor, args.neighbor_port, args.dealer)
    node.establish_connection()

    game = Game(node.machines, node)
    while not game.ended:
        if not game.dead:
            print("\n--------------------------------------------------------------------------")
            game.clear_state()
            print(f"Iniciando round: {game.rounds} - Minhas vidas: {game.lifes}")

            if not node.dealer: 
                game.receive_cards()
            else: 
                game.shuffle_and_distribute()

            time.sleep(1)
            game.show_cards()

            print(f"Vira da rodade eh: {game.turn}\n")

            game.bet_wins()
            game.show_bets()
            time.sleep(1)

            for r_index in range(Constants.ROUNDS):
                print(f"Rodada {r_index + 1}")
                print("Aguardando jogadas...\n")
                moves = game.make_move()
                game.compute_results(moves)
                time.sleep(1)

            game.check_round_result()
            game.still_alive()
            game.game_ended()
            time.sleep(1)
            
            if not game.ended:
                game.pass_dealer()

                game.rounds += 1
                time.sleep(1)
            print("--------------------------------------------------------------------------\n")

        else:
            game.dead_mode()
            print("Pacote recebido, retransferindo...")
            time.sleep(1)
        
        time.sleep(2)
    print("Jogo acabou!\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="dealer Ring Network", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("-m", "--machine", type=str, required=True)
    parser.add_argument("-p", "--port", type=int, required=True)
    parser.add_argument("-n", "--neighbor", type=str, required=True)
    parser.add_argument("-np", "--neighbor_port", type=int, required=True)
    parser.add_argument("-d", "--dealer", type=int, required=True)

    main(parser.parse_args())
