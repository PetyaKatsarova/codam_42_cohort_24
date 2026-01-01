
/**
 * our program must be able to use a positive integer sequence as an argument.
• Your program must use the merge-insert sort algorithm to sort the positive integer
sequence. you need to use the Ford-Johnson algorithm.
(source: Art Of Computer Programming, Vol.3. Merge Insertion,
Page 184.)
• If an error occurs during program execution, an error message should be displayed
on the standard error.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.
It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.
 */

 #include <iostream>
 #include <vector>
 #include <algorithm>
 #include <utility> // std::pair??

void printArr(std::vector<int>& arr) {
	std::cout << "[";
	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i];
		if (i < arr.size() - 1) std::cout << ", ";
	}
	std::cout << "]\n";
}

void printPairs(const std::vector<std::pair<int, int>>& pairs) {
	std::cout << "Pairs: ";
	for (const auto& p : pairs) { // doesnt take in int
		std::cout << "(" << p.first << ", " << p.second << ")";
	}
	std::cout << "\n";
}

// Step 1: Create pairs with larger element first
std::vector<std::pair<int, int>> makePairs(const std::vector<int>& arr, int& oddEl) {
	std::vector<std::pair<int, int>> pairs;

	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i] < arr[i+1]) {
			pairs.push_back({arr[i+1], arr[i]}); 
		} else {
			pairs.push_back({arr[i], arr[i+1]});
		}
	}
	oddEl = (arr.size() % 2 == 1 ? arr.back() : -1); // save odd el if arr has odd len
	return pairs;
}

// step 2: sort pairs by their first(larger) el
void sortPairs(std::vector<std::pair<int, int>>& pairs) {
	std::sort(pairs.begin(), pairs.end());
}

// step 3: make new vector: only from the all first els from the vector of pairs
std::vector<int> extractMainChain(const std::vector<std::pair<int, int>>& pairs) {
	std::vector<int> mainChain;

	for (auto& pair : pairs) {
		mainChain.push_back(pair.first);
	}
	return mainChain;
}

// step 4: create array of the second int from the pair
std::vector<int> extractPendingElements(const std::vector<std::pair<int, int>>& pairs) {
	std::vector<int> result;

	for (auto&p : pairs) {
		result.push_back(p.second);
	}
	return result;
}

/**
 * step 5:
 * std::lower_bound is a standard algorithm that finds the first position in a sorted range where a given value can be inserted
 *  without violating the ordering, i.e., it returns an iterator to the first element that is not less than the specified value.
 * Insert element using binary search
 */
void insertElement(std::vector<int>& mainChain, int num) {
	auto pos = std::lower_bound(mainChain.begin(), mainChain.end(), num); // auto will be iterator, not int
	mainChain.insert(pos, num);
}

/**
 * step 6: 
 */
void insertPending(std::vector<int>& mainChain, std::vector<int>& pendingChain) {
	for (auto& p : pendingChain) {
		insertElement(mainChain, p);
	}
}

// step 7: put all together and if odd num of el in arr: insert it, too
void fordJohnsonSort(std::vector<int>& arr) {
	int oddEl = -1;
	std::vector<std::pair<int, int>> pairs = makePairs(arr, oddEl); // 1: 
	printPairs(pairs);
	sortPairs(pairs); // 2
	printPairs(pairs);
	std::vector<int> mainChain = extractMainChain(pairs); // 3 
	printArr(mainChain);
	std::vector<int> pendingEls = extractPendingElements(pairs); // 4
	printArr(pendingEls);
	insertPending(mainChain, pendingEls); // 5

	if (oddEl != -1) {
		insertElement(mainChain, oddEl);
	}
	printArr(mainChain);
}

std::vector<int> bigArr= {
	4481,42964,83214,83005,40026,70362,28587,63968,76817,24594,11799,60772,95731,50086,71034,3764,56684,39420,2749,35527,
	44219,1123,69246,16726,82633,99777,98108,46158,33251,14800,65938,63572,66892,32328,65374,36913,92889,1388,92506,7802,
	99512,27670,84404,43392,190,26106,20362,58037,8110,90738,25901,57454,87364,5704,95573,57624,55202,73842,68997,51252,
	31768,94743,68842,40929,55346,37148,42023,92516,365,74979,38419,43961,20460,79821,38761,75781,89835,31279,54361,4303,
	40374,91492,3056,54103,7255,50758,2710,2363,3253,75769,17459,47552,62542,54823,25792,57792,96176,90208,99411,63778,
	59962,43627,28719,17816,47813,61715,68305,92399,83431,48329,58179,47766,99687,63317,79715,77456,57839,91487,21664,
	78436,56686,85446,79457,57281,95170,48211,72312,39562,37307,42852,33538,90557,79900,45283,67141,93543,57886,92079,
	54971,25144,77980,7707,18815,59544,18581,21261,33325,71663,49438,30557,62835,35972,45639,76713,24151,47031,96612,
	79053,71718,90507,9190,43309,47034,85907,65048,99770,6901,83245,77735,44395,7109,57308,35811,67965,54005,7821,
	94166,755,97248,80092,20394,61333,7820,33464,58313,76284,49607,29656,92182,3884,63000,72931,47832,47758,87813,
	60748,83137,89029,52493,47119,41349,88825,30151,3448,24833,3019,61349,44882,10743,95714,16094,38907,46025,742,40621,
	72674,55293,58287,26437,72241,60143,15795,61775,75316,55045,81491,75085,26027,32337,54047,74573,28552,82813,67641,73270,
	56957,36475,19421,51161,13181,98142,44417,40758,81209,37808,26671,60680,59558,32330,96218,92729,2461,25768,40504,109,26519,
	90103,80520,19111,12108,78880,82611,74350,23355,44938,51272,77363,16445,35774,89810,3231,68730,30767,1405,71812,97795,58143,
	64235,29346,66792,6827,21198,14310,33419,21194,69098,59931,44311,87545,25557,97886,69272,95961,71488,37336,1832,28432,22823,
	43068,74156,92061,1743,32069,38352,25139,64042,94205,37286,62356,4988,66929,73949,48603,40121,35366,7240,39869,57094,68370,
	18181,39947,37691,59592,42222,64423,87432,43199,48017,29878,93262,64709,42004,3911,21931,2009,52106,35350,96986,22087,40776,
	84997,8223,15957,77890,62242,56181,47134,63641,40800,16331,52463,69483,49237,3018,27598,25404,53985,17170,60785,55141,84176,
	53732,89830,29695,99345,48995,98643,32307,57258,9598,76054,25889,42278,31430,92230,37930,56404,35890,95125,45301,62605,35658,
	37159,93343,62612,17879,42842,45631,32257,46488,90185,21126,49956,18249,83030,27882,20124,69953,25023,67969,67536,65788,46208,
	27480,22793,2961,35397,17594,50658,65335,60272,1218,56015,18724,3670,39117,38801,21411,61408,68567,27096,94894,74082,8391,98845,
	65746,97523,63366,30016,97911,71775,75307,43766,69303,6836,62018,15160,89066,15267,17911,78003,63431,70646,9923,39211,74227,
	64852,9021,49137,91177,32517,5071,35915,5763,79664,59893,22962,41073,72169,93081,86930,83784,15626,59837,52926,72221,93829,94805,
	63127,70903,56854,94800,54592,86126,74959,55014,20186,27091,74757,9219,68460,14435,94720,64257,44184,49285,55951,24671,91741,16785,
	55312,92048,99152,99548,47732,64250,37673,83369,58950,79058,93323,97950,16348,82807,62268,61239,87580,11046,80078,93728,43766,
	67557,66064,55717,5425,88206,35066,89596,34531,33395,70866,64927,41202,7964,56761,73836,55677,22661,97326,72588,14136,17882,33682,
	80661,37121,98414,50194,80391,98058,98,5581,84154,93636,3268,67536,45356,64966,47605,94282,41566,6679,34063,87312,88896,48503,97110,
	58735,70702,11141,42353,26411,67792,96170,4812,68572,3431,36991,30077,5503,61448,9573,90285,42915,42004,38661,2065,4112,92353,45736,
	18319,36400,29192,51258,42068,70538,27301,29329,74191,57420,90052,47307,65692,53793,88560,85770,39016,39133,56912,28277,1314,35853,
	67629,79952,83005,31064,16976,62776,86505,9446,33081,59545,95498,2082,1456,76111,52039,20558,91044,94877,94416,45534,78848,28561
};

// c++ main.cpp && ./a.out
 int main() {
	std::vector<int> arr = {1, 3, 442, 3, 43, 8};
	// printArr(arr);
	// fordJohnsonSort(arr);

	std::vector<int> oddArr = {1, 2222, 42, 15, 2, 8, 7};
	fordJohnsonSort(oddArr);
	
	return 0;
 }