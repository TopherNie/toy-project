#!/usr/bin/env python3

"""Texas holdem hand evaluation."""

# pylint: disable=too-many-statements, too-many-branches, too-many-locals

CARD_RANKS_ORIGINAL = '23456789TJQKA'
SUITS_ORIGINAL = 'cdhs'


def cal_score_to_hot_encoding_str(hand_str):
    if not hand_str:
        print("The parameter [hand_str] is empty!")
        return -1
    sep = "-"
    hand = hand_str.split(sep)

    hand_type, win_card_indexes = calc_score(hand)
    hand_size = len(hand)
    hot_encoding_list = [1 if i in win_card_indexes else 0 for i in range(0, hand_size)]
    hot_encoding_str_list = map(lambda x: str(x), hot_encoding_list)
    hot_encoding_str = sep.join(hot_encoding_str_list)
    return hand_type + " " + hot_encoding_str


def calc_score(hand):
    card_size = len(hand)
    """Assign a calc_score to the hand so it can be compared with other hands"""
    rcount_dict = {CARD_RANKS_ORIGINAL.find(r): ''.join(hand).count(r) for r, _ in hand}
    rcounts = rcount_dict.items()
    score, card_ranks = zip(*sorted((cnt, rank) for rank, cnt in rcounts)[::-1])

    flush_suit = None
    straight = False

    potential_threeofakind = score[0] == 3
    potential_twopair = score == (2, 2, 1, 1, 1) or score == (2, 2, 1, 1) or score == (2, 2, 1)
    potential_pair = score == (2, 1, 1, 1, 1, 1) or score == (2, 1, 1, 1, 1) or score == (2, 1, 1, 1)

    if score[0:2] == (3, 2) or score[0:2] == (3, 3):  # fullhouse (three of a kind and pair, or two three of a kind)
        card_ranks = (card_ranks[0], card_ranks[1])
        score = (3, 2)
    elif score[0:4] == (2, 2, 2, 1) or score[0:3] == (2, 2, 2):  # special case: convert three pair to two pair
        score = (2, 2, 1)  # as three pair are not worth more than two pair
        kicker = max(card_ranks[2], card_ranks[3])  # avoid for example 11,8,6,7
        card_ranks = (card_ranks[0], card_ranks[1], kicker)
    elif score[0] == 4:  # four of a kind
        score = (4,)
        # sorted_card_ranks = sorted(card_ranks, reverse=True)  # avoid for example 11,8,9
        # card_ranks = (sorted_card_ranks[0], sorted_card_ranks[1])
        card_ranks = (card_ranks[0], card_ranks[1])
    elif len(score) >= 5:  # high card, flush, straight and straight flush
        # straight
        if 12 in card_ranks:  # adjust if 5 high straight
            card_ranks += (-1,)
        sorted_card_ranks = sorted(card_ranks, reverse=True)  # sort again as if pairs the first rank matches the pair
        for i in range(len(sorted_card_ranks) - 4):
            straight = sorted_card_ranks[i] - sorted_card_ranks[i + 4] == 4
            if straight:
                card_ranks = (
                    sorted_card_ranks[i], sorted_card_ranks[i + 1], sorted_card_ranks[i + 2], sorted_card_ranks[i + 3],
                    sorted_card_ranks[i + 4])
                break

        # flush
        suits = [s for _, s in hand]
        flush = max(suits.count(s) for s in suits) >= 5

        if flush:
            for flush_suit in SUITS_ORIGINAL:  # get the suit of the flush
                if suits.count(flush_suit) >= 5:
                    break

            flush_hand = [k for k in hand if flush_suit in k]  # pylint: disable=undefined-loop-variable
            rcounts_flush = {CARD_RANKS_ORIGINAL.find(r): ''.join(flush_hand).count(r) for r, _ in flush_hand}.items()
            score, card_ranks = zip(*sorted((cnt, rank) for rank, cnt in rcounts_flush)[::-1])
            card_ranks = tuple(
                sorted(card_ranks, reverse=True))  # ignore original sorting where pairs had influence

            # check for straight in flush
            if 12 in card_ranks and -1 not in card_ranks:  # adjust if 5 high straight
                card_ranks += (-1,)
            for i in range(len(card_ranks) - 4):
                straight = card_ranks[i] - card_ranks[i + 4] == 4
                if straight:
                    break

        # no pair, straight, flush, or straight flush
        score = ([(1,), (3, 1, 2)], [(3, 1, 3), (5,)])[flush][straight]

    if score == (1,) and potential_threeofakind:
        score = (3, 1)
    elif score == (1,) and potential_twopair:
        score = (2, 2, 1)
    elif score == (1,) and potential_pair:
        score = (2, 1, 1)

    if score[0] == 5:
        hand_type = "StraightFlush"   # crdRanks=crdRanks[:5] # five card rule makes no difference {:5] would be incorrect
    elif score[0] == 4:
        hand_type = "FourOfAKind"  # crdRanks=crdRanks[:2] # already implemented above
    elif score[0:2] == (3, 2):
        hand_type = "FullHouse"  # crdRanks=crdRanks[:2] # already implmeneted above
    elif score[0:3] == (3, 1, 3):
        hand_type = "Flush"
        card_ranks = card_ranks[:5]
    elif score[0:3] == (3, 1, 2):
        hand_type = "Straight"
        card_ranks = card_ranks[:5]
    elif score[0:2] == (3, 1):
        hand_type = "ThreeOfAKind"
        card_ranks = card_ranks[:3]
    elif score[0:2] == (2, 2):
        hand_type = "TwoPair"
        card_ranks = card_ranks[:3]
    elif score[0] == 2:
        hand_type = "Pair"
        card_ranks = card_ranks[:4]
    elif score[0] == 1:
        hand_type = "HighCard"
        card_ranks = card_ranks[:5]
    else:
        raise Exception('Card Type error!')

    win_card_indexes = get_win_card_indexes(hand, card_ranks, rcount_dict, flush_suit, straight)

    return hand_type, win_card_indexes


# Find the i-th index of one element in the list
# Wrote by Nie Tao on 12/23/2019
def get_card_index(card_arr, find_card, i):
    count = 0
    for j, card in enumerate(card_arr):
        # String contains
        if find_card in card:
            if count == i:
                return j
            count += 1
    return -1


# Wrote by Nie Tao on 12/23/2019
def get_win_card_indexes(hand, card_ranks, rcount_dict, flush_suit, is_straight):
    res = []
    for rank in card_ranks:
        card = CARD_RANKS_ORIGINAL[rank]
        if flush_suit:
            card += flush_suit
        if is_straight or flush_suit:
            res.append(get_card_index(hand, card, 0))
        else:
            r_count = rcount_dict[rank]
            multiple_indexes = [get_card_index(hand, card, i) for i in range(r_count)]
            res += multiple_indexes
    return sorted(res[: 5])


if __name__ == "__main__":
    hand_str = "9c-9h-3d-Ks-9d-9s"
    re = cal_score_to_hot_encoding_str(hand_str)
    print(re)


