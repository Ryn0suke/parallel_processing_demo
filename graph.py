import polars as pl
import matplotlib.pyplot as plt

def main():
    # CSVファイルの読み込み
    df_process = pl.read_csv("./result/multi_process.csv")
    df_thread = pl.read_csv("./result/multi_thread.csv")

    print(df_process.columns)


    # グラフ作成
    plt.figure(figsize=(10, 6))
    plt.plot(df_process["Processes"].to_list(), df_process["Time"].to_list(), marker='o', label="Processes")
    plt.plot(df_thread["Threads"].to_list(), df_thread["Time"].to_list(), marker='o', label="Threads")

    # グラフの装飾
    plt.title("Processing Time vs Number of Processes/Threads", fontsize=14)
    plt.xlabel("Number of Processes/Threads", fontsize=12)
    plt.ylabel("Time (seconds)", fontsize=12)
    plt.grid(True)
    plt.xticks(df_process["Processes"].to_list())
    plt.legend()
    plt.tight_layout()

    # グラフの保存
    plt.savefig("./fig/result.png")

if __name__ == "__main__":
    main()
