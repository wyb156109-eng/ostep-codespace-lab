## Q1
- Prediction / 預測: Total Time: 10, CPU Busy: 10 (100%), IO Busy: 0
```text
Time | PID 0 | PID 1 | CPU | IOs
--- | --- | --- | --- | ---
1 | RUN:cpu | READY | 1 | 
2 | RUN:cpu | READY | 1 | 
3 | RUN:cpu | READY | 1 | 
4 | RUN:cpu | READY | 1 | 
5 | RUN:cpu | READY | 1 | 
6 | DONE | RUN:cpu | 1 | 
7 | DONE | RUN:cpu | 1 | 
8 | DONE | RUN:cpu | 1 | 
9 | DONE | RUN:cpu | 1 | 
10 | DONE | RUN:cpu | 1 |
- Reasoning / 理由: 两个进程都只有 CPU 指令（100% CPU），完全没有 I/O 操作。因此，PID 0 会先连续执行 5 个 tick 直到结束，期间 PID 1 处于 READY 状态。接着 PID 1 再执行 5 个 tick。因为没有任何 I/O 等待，CPU 会一直处于忙碌状态，不会闲置。

- Verified result / 驗證結果: Total Time 10, CPU Busy 10 (100.00%)
- Analysis / 分析: 預測完全正確。因為只有 CPU 指令，沒有 I/O 阻塞，CPU 全程保持忙碌狀態，總時間就是兩個進程指令數的總和。
## Q2
- Prediction / 預測: Total Time: 11, CPU Busy: 6 (54.5%), IO Busy: 7
```text
Time | PID 0 | PID 1 | CPU | IOs
--- | --- | --- | --- | ---
1 | RUN:cpu | READY | 1 | 
2 | RUN:cpu | READY | 1 | 
3 | RUN:cpu | READY | 1 | 
4 | RUN:cpu | READY | 1 | 
5 | DONE | RUN:io | 1 | 1
6 | DONE | BLOCKED |   | 1
7 | DONE | BLOCKED |   | 1
8 | DONE | BLOCKED |   | 1
9 | DONE | BLOCKED |   | 1
10 | DONE | BLOCKED |   | 1
11* | DONE | RUN:io_done | 1 | 1
- Reasoning / 理由: PID 0 有 4 條 CPU 指令，先連續執行完。接著換 PID 1，它有一條 I/O 指令。發起 I/O 需 1 tick，等待磁碟需 5 ticks (此時 CPU 空閒)，最後處理 I/O 結束需 1 tick。總共耗時 11 ticks，其中 CPU 只有 6 ticks 在做事。
- Verified result / 驗證結果: Total Time 11, CPU Busy 6 (54.55%)
- Analysis / 分析: 預測完全正確。發起 I/O 需要 1 tick，等待 5 ticks，處理完成需要 1 tick。在等待的 5 ticks 期間，沒有其他進程可以使用 CPU，因此 CPU 利用率下降。
## Q3
- Prediction / 預測: Total Time: 7, CPU Busy: 6 (85.7%), IO Busy: 7
```text
Time | PID 0 | PID 1 | CPU | IOs
--- | --- | --- | --- | ---
1 | RUN:io | READY | 1 | 1
2 | BLOCKED | RUN:cpu | 1 | 1
3 | BLOCKED | RUN:cpu | 1 | 1
4 | BLOCKED | RUN:cpu | 1 | 1
5 | BLOCKED | RUN:cpu | 1 | 1
6 | BLOCKED | DONE |   | 1
7* | RUN:io_done | DONE | 1 | 1
- Reasoning / 理由: 因為 PID 0 一開始就去弄 I/O 卡住了（BLOCKED），系統很聰明，馬上把 CPU 切換給 PID 1 用。等 PID 1 跑完 4 個 CPU 指令，PID 0 的 I/O 也剛好快結束了。這樣重疊執行省了很多時間，總共只要 7 個 tick 就跑完。
- Verified result / 驗證結果: Total Time 7, CPU Busy 6 (85.71%)
- Analysis / 分析: 預測完全正確。系統在 PID 0 等待 I/O 時，成功切換給 PID 1 執行 CPU 指令，完美實現了重疊執行（Overlap），大幅縮短了總運行時間。
## Q4
- Prediction / 預測: Total Time: 11, CPU Busy: 6 (54.5%), IO Busy: 7
```text
Time | PID 0 | PID 1 | CPU | IOs
--- | --- | --- | --- | ---
1 | RUN:io | READY | 1 | 1
2 | BLOCKED | READY |   | 1
3 | BLOCKED | READY |   | 1
4 | BLOCKED | READY |   | 1
5 | BLOCKED | READY |   | 1
6 | BLOCKED | READY |   | 1
7* | RUN:io_done | READY | 1 | 1
8 | DONE | RUN:cpu | 1 | 
9 | DONE | RUN:cpu | 1 | 
10 | DONE | RUN:cpu | 1 | 
11 | DONE | RUN:cpu | 1 |
- Reasoning / 理由:因為加上了 -S SWITCH_ON_END 參數，系統規定一定要等當前進程徹底結束才會切換。所以當 PID 0 卡在 BLOCKED 等待 I/O 時，作業系統不會把 CPU 借給 PID 1。CPU 會直接白白閒置 5 個 tick，直到 PID 0 整個結束（第 7 個 tick），PID 1 才能開始跑。這導致完全沒有重疊（Overlap），總時間拉長到 11。
- Verified result / 驗證結果: Total Time 11, CPU Busy 6 (54.55%)
- Analysis / 分析: 預測完全正確。因為加上了 `-S SWITCH_ON_END`，系統被迫等待 PID 0 完全結束（包含漫長的 I/O 等待）才能切換進程，導致 CPU 白白閒置，失去了重疊執行的優勢。
## Q5
- Prediction / 預測: Total Time: 7, CPU Busy: 6 (85.7%), IO Busy: 7
```text
Time | PID 0 | PID 1 | CPU | IOs
--- | --- | --- | --- | ---
1 | RUN:io | READY | 1 | 1
2 | BLOCKED | RUN:cpu | 1 | 1
3 | BLOCKED | RUN:cpu | 1 | 1
4 | BLOCKED | RUN:cpu | 1 | 1
5 | BLOCKED | RUN:cpu | 1 | 1
6 | BLOCKED | DONE |   | 1
7* | RUN:io_done | DONE | 1 | 1
- Reasoning / 理由:參數 -S SWITCH_ON_IO 的意思是「遇到 I/O 就切換」，這其實就是系統預設的行為。所以這題的結果和 Q3 完全一模一樣，總時間 7。
- Verified result / 驗證結果: Total Time 7, CPU Busy 6 (85.71%)
- Analysis / 分析: 預測完全正確。`-S SWITCH_ON_IO` 是系統的預設高效行為，遇到 I/O 就立刻釋放 CPU 給其他進程，結果與 Q3 一致。
## Q6
- Prediction / 預測:Total Time: 31, CPU Busy: 21 (67.7%), IO Busy: 15
```text
Time | PID 0 | PID 1 | PID 2 | PID 3 | CPU | IOs
--- | --- | --- | --- | --- | --- | ---
1 | RUN:io | READY | READY | READY | 1 | 1
2 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
3 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
4 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
5 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
6 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
7* | RUN:io_done | DONE | READY | READY | 1 | 
8 | READY | DONE | RUN:cpu | READY | 1 | 
9 | READY | DONE | RUN:cpu | READY | 1 | 
10 | READY | DONE | RUN:cpu | READY | 1 | 
11 | READY | DONE | RUN:cpu | READY | 1 | 
12 | READY | DONE | RUN:cpu | READY | 1 | 
13 | READY | DONE | DONE | RUN:cpu | 1 | 
14 | READY | DONE | DONE | RUN:cpu | 1 | 
15 | READY | DONE | DONE | RUN:cpu | 1 | 
16 | READY | DONE | DONE | RUN:cpu | 1 | 
17 | READY | DONE | DONE | RUN:cpu | 1 | 
18 | RUN:io | DONE | DONE | DONE | 1 | 1
19 | BLOCKED | DONE | DONE | DONE |   | 1
20 | BLOCKED | DONE | DONE | DONE |   | 1
21 | BLOCKED | DONE | DONE | DONE |   | 1
22 | BLOCKED | DONE | DONE | DONE |   | 1
23 | BLOCKED | DONE | DONE | DONE |   | 1
24* | RUN:io_done | DONE | DONE | DONE | 1 | 
25 | RUN:io | DONE | DONE | DONE | 1 | 1
26 | BLOCKED | DONE | DONE | DONE |   | 1
27 | BLOCKED | DONE | DONE | DONE |   | 1
28 | BLOCKED | DONE | DONE | DONE |   | 1
29 | BLOCKED | DONE | DONE | DONE |   | 1
30 | BLOCKED | DONE | DONE | DONE |   | 1
31* | RUN:io_done | DONE | DONE | DONE | 1 |
- Reasoning / 理由:參數 -I IO_RUN_LATER 代表當 I/O 結束時，發起 I/O 的 PID 0 不會立刻搶回 CPU，而是被丟到 READY 佇列排隊等待。這導致 PID 0 必須等 PID 2 和 3 把所有 CPU 指令都跑完後，才能繼續發起剩下的兩次 I/O。後面 10 幾個 tick I/O 設備都在單獨運作，CPU 白白閒置，浪費了重疊執行的機會。
- Verified result / 驗證結果: Total Time 31, CPU Busy 21 (67.74%)
- Analysis / 分析: 預測完全正確。`-I IO_RUN_LATER` 讓發起 I/O 的進程在 I/O 結束後必須重新排隊，導致後續的 I/O 請求被嚴重推遲，在所有進程的 CPU 指令跑完後，只剩下 I/O 在單獨運作，效率低落。
## Q7
- Prediction / 預測:Total Time: 21, CPU Busy: 21 (100%), IO Busy: 15
```text
Time | PID 0 | PID 1 | PID 2 | PID 3 | CPU | IOs
--- | --- | --- | --- | --- | --- | ---
1 | RUN:io | READY | READY | READY | 1 | 1
2 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
3 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
4 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
5 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
6 | BLOCKED | RUN:cpu | READY | READY | 1 | 1
7* | RUN:io_done | DONE | READY | READY | 1 | 
8 | RUN:io | DONE | READY | READY | 1 | 1
9 | BLOCKED | DONE | RUN:cpu | READY | 1 | 1
10 | BLOCKED | DONE | RUN:cpu | READY | 1 | 1
11 | BLOCKED | DONE | RUN:cpu | READY | 1 | 1
12 | BLOCKED | DONE | RUN:cpu | READY | 1 | 1
13 | BLOCKED | DONE | RUN:cpu | READY | 1 | 1
14* | RUN:io_done | DONE | DONE | READY | 1 | 
15 | RUN:io | DONE | DONE | READY | 1 | 1
16 | BLOCKED | DONE | DONE | RUN:cpu | 1 | 1
17 | BLOCKED | DONE | DONE | RUN:cpu | 1 | 1
18 | BLOCKED | DONE | DONE | RUN:cpu | 1 | 1
19 | BLOCKED | DONE | DONE | RUN:cpu | 1 | 1
20 | BLOCKED | DONE | DONE | RUN:cpu | 1 | 1
21* | RUN:io_done | DONE | DONE | DONE | 1 |
- Reasoning / 理由:參數 -I IO_RUN_IMMEDIATE 是非常高效的設定！它代表只要 I/O 一完成，PID 0 就可以立刻插隊搶回 CPU 發起下一次 I/O。這使得 PID 0 的三次 I/O 等待時間，完美地與 PID 1、2、3 的 CPU 運算時間重疊。CPU 和 I/O 設備全程都沒有閒置，達到了最高效率
- Verified result / 驗證結果: Total Time 21, CPU Busy 21 (100.00%)
- Analysis / 分析: 預測完全正確。`-I IO_RUN_IMMEDIATE` 允許 I/O 一結束就立刻搶回 CPU 繼續發起下一次 I/O，完美利用了所有 CPU 的空檔，達到了 100% 的 CPU 利用率，總時間最短。
## Q8
- Prediction / 預測:使用預設或 SWITCH_ON_END 時，如果隨機生成的指令是 I/O 和 CPU 混雜，系統很容易因為等待 I/O 而讓 CPU 閒置，導致整體時間拉長、效能低落。

若加上 -I IO_RUN_IMMEDIATE 參數，無論隨機指令怎麼排，系統都能強制讓頻繁發起 I/O 的進程優先插隊處理，最大化 CPU 和 I/O 的重疊執行（Overlap），因此總執行時間一定是最短的。
- Reasoning / 理由:第 8 題使用 -s 1, 2, 3 隨機生成指令。我們無法提前畫出確切的表格，但底層邏輯是不變的：一個優秀的作業系統排程器，必須優先處理 I/O 密集型任務（IO_RUN_IMMEDIATE），讓硬碟保持運作，同時把 CPU 空檔分給 CPU 密集型任務，才能榨乾電腦的效能。
- Verified result / 驗證結果: 模擬器產生的 q8-s1 等檔案證實，在各種隨機種子下，加上 `-I IO_RUN_IMMEDIATE` 參數的總執行時間始終是最短的。
- Analysis / 分析: 預測與實際測試結果相符。優化排程策略（優先處理 I/O 密集型任務並允許立刻接續執行）能在不可預測的真實指令序列中，穩定地將系統效能最大化。