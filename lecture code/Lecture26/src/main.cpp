/*
* CS 106B/X, Julie Zelenski
*
* This program contains code for various algorithms and a timing harness
* to measure the runtime for different size inputs. It recprds the times
* observed and passes off data to JavaScript to graph results.
*/

#include <iostream>
#include <iomanip>
#include "timer.h"
#include "vector.h"
#include "set.h"
#include "console.h"
using namespace std;

// function prototype declarations
int findMax(Vector<int> &v);
int findMin(Vector<int> &v);
int getRange(Vector<int> &v);
int getRangeOnePass(Vector<int> &v);
int linearSearch(Vector<int> &v, int target);
int binarySearch(Vector<int> &v, int target);
int findUnsuccessful(Vector<int> &v);
int findSuccessful(Vector<int> &v);
int findUnsuccessfulSorted(Vector<int> &v);
int findSuccessfulSorted(Vector<int> &v);
int countDuplicates(Vector<int> &v);
int countDuplicatesSorted(Vector<int> &v);
int countDuplicatesUsingSet(Vector<int> &v);
int selectionSort(Vector<int> &v);;
int insertionSort(Vector<int> &v);
int mergeSort(Vector<int> &v);

void fillRandom(Vector<int> &v, int size, bool sorted);
typedef int (*Job)(Vector<int> &v);
void time_job(Map<string, Vector<Point>>& map, string name, Job job, int base_size, bool sorted = false, int nDoubles = 8);
void assertSorted(Vector<int>& v);




int main()
{
   Map<string, Vector<Point>> map;  // record timing data points to graph later

   int base_size;
   base_size = 40000; // recommend 40000
   time_job(map, "Find minimum", findMin, base_size);
   time_job(map, "Find maximum", findMax, base_size);
   time_job(map, "Get range (min AND max, two passes)", getRange, base_size);
   time_job(map, "Get range (min AND max, one combined pass)", getRangeOnePass, base_size);

   base_size = 200000; // recommend 200000
   time_job(map, "Linear search unsuccessful (worst case)", findUnsuccessful, base_size);
   time_job(map, "Linear search successful (specific case)", findSuccessful, base_size);
   time_job(map, "Binary search unsuccessful (worst case)", findUnsuccessfulSorted, base_size, true);
   time_job(map, "Binary search successful (specific case)", findSuccessfulSorted, base_size, true);

   base_size = 1000; // recommend 1000
   time_job(map, "Count all duplicates", countDuplicates, base_size, false, 6);
   time_job(map, "Count all duplicates using Set", countDuplicatesUsingSet, base_size, true, 11);
   time_job(map, "Count all duplicates sorted", countDuplicatesSorted, base_size, true, 11);

   base_size = 100;// recommend 200
   time_job(map, "Selection sort", selectionSort, base_size);
   time_job(map, "Insertion sort", insertionSort, base_size);
   time_job(map, "Merge sort", mergeSort, base_size, false, 11);

   cout << " All Done!" << endl;
   return 0;
}

void time_job(Map<string, Vector<Point>>& map, string name, Job job, int base_size, bool sorted, int nDoublings)
{
   Timer timmy;
   Vector<int> v;

   cout << endl << "Timing operation: " << name << endl;
   int factor = 1;
   for (int i = 0; i < nDoublings; i++, factor *=2) {
       int size = base_size*factor;
       fillRandom(v, size, sorted);
       cout << setw(10) << size << " (" << setw(5) << factor << "X) elements" << flush;
       timmy.start();
       job(v);
       int elapsed = timmy.stop();
       cout << " took " << setw(6) << elapsed << " msecs" << endl;
       map[name].add( {size, elapsed} );
   }
}


/*
* Examines each element in vector, tracking largest seen.
* Returns maximum value.
* O(N)
*/
int findMax(Vector<int> &v)
{
   int max = v[0];
   for (int i = 1; i < v.size(); i++) {
       if (v[i] > max) {
           max = v[i];
       }
   }
   return max;
}

/*
* Examines each element in vector, tracking smallest seen.
* Returns minimum value.
* O(N)
*/
int findMin(Vector<int> &v)
{
   int min = v[0];
   for (int i = 1; i < v.size(); i++) {
       if (v[i] < min) {
           min = v[i];
       }
   }
   return min;
}

/*
* This version of getRange leverages the existing findMin/findMax
* rather than write any new code.
* O(N) + O(N) = O(N)
*/
int getRange(Vector<int> &v)
{
   int min = findMin(v);
   int max = findMax(v);
   return max - min + 1;
}

/*
* This version of getRange tracks the min and max simultaneously while
* making one single pass over the vector.
*/
int getRangeOnePass(Vector<int> &v)
{
   int min = v[0], max = v[0];
   for (int i = 1; i < v.size(); i++) {
       if (v[i] < min) {
           min = v[i];
       } else if (v[i] > max) {
           max = v[i];
       }
   }
   return max - min + 1;
}


/*
* This version compares each element in the vector to find a match to the target.
* Returns index of match or -1 if not found.
* O(N)
*/
int linearSearch(Vector<int> &v, int target)
{
   for (int i = 0; i < v.size(); i++) {
       if (v[i] == target) {
           return i;
       }
   }
   return -1;
}

/*
* This version searches for a match to target using a binary search strategy.
* Vector must be in sorted order. A binary search proceeds
* by comparing the target to the midpoint element and then narrowing the
* search to just the appropriate half from there.
* Returns index of match or -1 if not found.
* O(logN)
*/
int binarySearch(Vector<int> &v, int target)
{
   int low = 0;
   int high = v.size() - 1;

   while (low <= high)  {
       int mid = (low + high)/2;
       if (v[mid] == target) {
           return mid;
       } else if (v[mid] < target) {
           low = mid + 1;
       } else {
           high = mid - 1;
       }
   }
   return -1;
}

/*
* Searches for an element known to not be in
* the vector. (Worst case for algorithm)
*/
int findUnsuccessful(Vector<int> &v)
{
   return linearSearch(v, -1);
}

/*
* Searches for an element known to be in
* the vector. (Average case for algorithm)
*/
int findSuccessful(Vector<int> &v)
{
   return linearSearch(v, randomElement(v));
}

int findUnsuccessfulSorted(Vector<int> &v)
{
   return binarySearch(v, -1);
}

int findSuccessfulSorted(Vector<int> &v)
{
   return binarySearch(v, randomElement(v));
}

/*
* Counts the number of duplicate elements in an unsorted
* vector. To determine if an element is a duplicate, searches
* over elements we have already seen.
* O(N^2)
*/
int countDuplicates(Vector<int> &v)
{
   int count = 0;
   for (int i = 0; i < v.size(); i++) {
       for (int j = 0; j < i; j++) {
           if (v[j] == v[i]) {
               count++;    // i is a duplicate
               break;
           }
       }
   }
   return count;
}

/*
* Counts the number of duplicate elements in a sorted
* vector. To determine if an element is a duplicate, merely
* need to comare with immediate neighbor.
* O(N)
*/
int countDuplicatesSorted(Vector<int> &v)
{
   int count = 0;
   for (int i = 0; i < v.size() - 1; i++) {
       if (v[i+1] == v[i]) {
           count++;
       }
   }
   return count;
}

/*
* Counts the number of duplicate elements in a vector.
* Uses a set to track all elements seen so far, and can
* determine if an element is a duplicate by checking the set.
* O(NlogN)
*/
int countDuplicatesUsingSet(Vector<int> &v)
{
   int count = 0;
   Set<int> seen;

   for (int i = 0; i < v.size(); i++) {
       if (!seen.contains(v[i])) {
           seen.add(v[i]);
       } else {
           count++;
       }
   }
   return count;
}


void fillRandom(Vector<int> &v, int size, bool sorted)
{
   srand(107); // force same seed for fairness
   v.clear();
   int last = 1;
   // ifsorted, has 10% duplicates
   for (int i = 1; i <= size; i++) {
       last = sorted ? randomInteger(last, last + 10) : randomInteger(1, size);
       v.add(last);
   }
}
void assertSorted(Vector<int> &v)
{
    for (int i = 1; i < v.size(); i++) {
        assert(v[i-1] <= v[i]);
    }
}

/*
 * This version finds the min of a subsection of the vector.
 */
int findMin(Vector<int> &v, int start)
{
    int minIndex = start;
    for (int i = start+1; i < v.size(); i++) {
        if (v[i] < v[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

void swap(Vector<int> &v, int x, int y)
{
    int tmp = v[x];
    v[x] = v[y];
    v[y] = tmp;
}

/* Inserts a value into a sorted subsection of vector v.
 * The elements from 0 to len-1 are in sorted order.
 */
void insertSorted(Vector<int> &v, int len, int val)
{
    int i;
    for (i = len - 1; i >= 0 && val < v[i]; i--) {
        v[i+1] = v[i];
    }
    v[i+1] = val;
}

/*
* Selection sort operates by scanning the data to find the minimum
* element and swapping to index [0]. The minimum element is
* now its in final position and no longer needs to considered.
* Repeats the process on the remaining elements to find the
* secondmost smallest to put into index [1] and so on.
* O(N^2)
*/
int selectionSort(Vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; i++) {
        int minIndex = findMin(v, i);
        swap(v, i, minIndex);
    }
    return 0;
}

/*
* Insertion sort operates by growing the sorted portion
* starting at index [0].  At iteration i of the loop, the elements in
* indexes [0] to [i-1] are in sorted order. The value at index [i]
* is then inserted into that sorted portion at the proper position.
* O(N^2)
*/
int insertionSort(Vector<int> &v)
{
    for (int i = 1; i < v.size(); i++) {
        insertSorted(v, i, v[i]);
    }
    return 0;
}


/*
* Merges two sorted vectors into one sorted result. The basic idea is
* to take the smaller of the next elements from a and b at each
* iteration. Be careful about when a or b has run out of elements.
* O(N)
*/
void merge(Vector<int> &result, Vector<int>& a, Vector<int> & b)
{
    int aIndex = 0, bIndex = 0;

    for (int i = 0; i < a.size() + b.size(); i++) {
        int next;
        if (bIndex >= b.size() || (aIndex < a.size() && a[aIndex] < b[bIndex])) {
             next = a[aIndex++];    // a's elem is smaller
        } else {
             next = b[bIndex++];    // b's elem is smaller
        }
        result.add(next);
    }
}

/*
* Merge sort operates by dividing the vector into two halves,
* both of which are recursively sorted and then merged
* into one sorted whole. The interesting work happens in
* the merge step.
* O(NlogN)
*/
int mergeSort(Vector<int> &v)
{
    if (v.size() > 1) {
        // divide elements into two halves
        Vector<int> front = v.subList(0,v.size()/2);
        Vector<int> back = v.subList(v.size()/2 + 1);
        v.clear();

        mergeSort(front);
        mergeSort(back);
        merge(v, front, back);
    }
    return 0;
}
