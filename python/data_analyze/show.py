import matplotlib.pyplot as plt
import pymysql
import sys
import pandas as pd
import os


def query_roleid(roleid):
    db = pymysql.connect("10.10.10.110", "root", "123456", "deep_texas")
    cursor = db.cursor()
    cursor.execute("select win,fail,score,hand,timeline from user_score_change where roleid=%d order by id asc"%(roleid,))
    results = cursor.fetchall()
    data = []
    for row in results:
        item = {
            'win': row[0],
            'fail': row[1],
            'score': row[2],
            'hand': row[3],
            'timeline': row[4],
            }
        data.append(item)
    return data


def draw(roleid, data):
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.set_title("roleid:%d" % (roleid,))
    xdata = [d['hand'] for d in data]
    # ax.plot(xdata, [d['win'] for d in data],label='win', color='tab:green')
    # ax.plot(xdata, [d['fail'] for d in data],label='fail', color='tab:red')
    ax.plot(xdata, [d['score'] for d in data], label='score', color='tab:blue')
    ax.legend()
    plt.show()


def draw_period(roleid, data):
    score_data = [d['score'] for d in data]
    data_count = len(score_data)
    score_data_period = [score_data[0]]
    score_data_period += [(score_data[i + 1] - score_data[i]) for i in range(data_count - 1)]

    score_data_period_win = filter(lambda x: x > 0, score_data_period)
    score_data_period_draw = filter(lambda x: x == 0, score_data_period)
    score_data_period_lose = filter(lambda x: x < 0, score_data_period)
    win_count = len(list(score_data_period_win))
    draw_count = len(list(score_data_period_draw))
    lose_count = len(list(score_data_period_lose))
    print("Data count: ", data_count)
    print("Win count: %d; Win rate: %f" % (win_count, win_count / data_count))
    print("Draw count: %d; Draw rate: %f" % (draw_count, draw_count / data_count))
    print("Lose count: %d; Lose rate: %f" % (lose_count, lose_count / data_count))
    print("Win data: ", score_data_period_win)

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.set_title("roleid:%d" % (roleid,))
    df = pd.DataFrame(score_data_period)
    df[0].hist(bins=data_count-1)
    plt.show()


def process(roleid):
    d = query_roleid(roleid)
    draw(roleid, d)
    draw_period(roleid, d)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("usage: python show.py roleid")
        sys.exit(1)
    roleid = 0
    try:
        roleid=int(sys.argv[1])
    except Exception as e:
        print("role error")
        sys.exit(1)
    process(roleid)

