In computer science, merge-insertion sort or the Ford–Johnson algorithm is a comparison sorting algorithm published in 1959 by L. R. Ford Jr. and Selmer M. Johnson.[1][2][3][4] It uses fewer comparisons in the worst case than the best previously known algorithms, binary insertion sort and merge sort,[1] and for 20 years it was the sorting algorithm with the fewest known comparisons.[5] Although not of practical significance, it remains of theoretical interest in connection with the problem of sorting with a minimum number of comparisons(wiki)

original [1, 3, 445, 3, 43, 8]

1. make pairs: 
(1, 3)  →  (3, 1)     // 3 > 1, so swap
(44445, 3)  →  (44445, 3)  // 44445 > 3, already correct
(43, 8)  →  (43, 8)   // 43 > 8, already correct

Pairs: [(3,1), (44445,3), (43,8)]

2. Sort Pairs by Their First Number
[(3,1), (43,8), (44445,3)]

3. Create Main Chain
[3, 43, 44445]

4. Save the Pending Numbers
[1, 8, 3]

5. Insert Pending Numbers Using Binary Search but up to the pair Max number

