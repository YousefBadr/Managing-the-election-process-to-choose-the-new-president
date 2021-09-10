# Managing-the-election-process-to-choose-the-new-president
A Parallel Project for Managing the election process to choose the new president written in C

Parallel scenario:
1. The master process takes the choice from user whether to generate a data file and calculate 
results or calculate results on data already stored.
2. The master process reads number of candidates and number of voters and then calculate 
remainder and portion size.
3. Each process takes its portion size from master process.
4. Each process opens the file and seek into it by the portion size assigned to it.
5. Each process calculates the voter’s most preferred candidate and then increase the candidate 
votes by one.
6. The master process handles the remainder (if exists).
7. The master process collects data from slaves and then it checks if a candidate has won from 
round one or we need another round.
8. If the master decides we need another round to settle the debate, the steps from four to seven 
are repeated with different instructions.
9. The master process decides after round two whether a candidate has won or it ended with a 
draw.
