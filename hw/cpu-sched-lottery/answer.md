Chapter 9git add . Homework

Q1: Ran `./lottery.py -j 3 -s 1 -c`, `-s 2`, `-s 3`. Winning tickets are generated randomly using total tickets. Output matches expectations.
Q2: `./lottery.py -l 10:1,10:100 -c`
    Job 0 (1 ticket) rarely runs before Job 1 (100 tickets) completes. The probability of Job 0 winning is only about 1/101 per lottery.
Q3: `./lottery.py -l 100:100,100:100 -c`
    With different seeds, they finish at slightly different times due to randomness (e.g., finishing at 192 vs 200). Fairness metric F is around 0.95 to 0.99, which is close to 1 but not perfectly fair.
Q4: As quantum size (-q) gets larger, fairness F gets worse (lower). Fewer lotteries mean more variance and less short-term fairness.
Q5: Stride scheduling would be perfectly deterministic (F closer to 1 at the end of each cycle), whereas Lottery has random fluctuations as seen in the chapter's graph.