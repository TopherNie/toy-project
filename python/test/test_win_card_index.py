from find_largest.hand_highlight import *

if __name__ == "__main__":
    hand_list = [
        ['Ac', '5c', 'Ah', 'Jc', 'Ah'],
        ['Jd', 'Js', '6d', '6s', 'Jh'],
        ['Ah', '4h', '3d', '3h', '5h', '2h', '7s']
    ]
    for hand in hand_list:
        hand_type, win_card_indexes = calc_score(hand)
        print("Hand: ", hand)
        print("Card type: ", hand_type)
        print("Win card indexes: ", win_card_indexes)
        print("=========================================")

    print("=========================================")
    card_str = "Ah-4h-3d-3h-5h-2h-7s"
    hot_encoding_str = cal_score_to_hot_encoding_str(card_str)
    card_str_2 = "Ac-Ad-Qd-Th-Ks-Js-2h"
    hot_encoding_str_2 = cal_score_to_hot_encoding_str(card_str_2)
    print(hot_encoding_str_2)


