#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>

using namespace std;

void selectionSort(int arr[], int n)
{
    // One by one move boundary of
    // unsorted subarray
    for (int i = 0; i < n - 1; i++)
    {
        // Find the minimum element in
        // unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int low, int high)
{

    // Choose the pivot
    int pivot = arr[high];

    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on the left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high)
{

    if (low < high)
    {

        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
int LinearSearch(int arr[], int N, int x)
{
    for (int i = 0; i < N; i++)
        if (arr[i] == x)
            return i;
    return -1;
}
int binarySearch(int arr[], int low, int high, int x)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return -1;
}
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
void sortingArray()
{
    int arr[2000];
    ifstream infile("array.txt");
    for (int i = 0; i < 5; ++i)
    {
        infile >> arr[i];
    }
    infile.close();
    int size = sizeof(arr) / sizeof(arr[0]);

    auto mergeSortstart = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1);
    auto mergeSortfinish = std::chrono::high_resolution_clock::now();
    int mergeSorttime = std::chrono::duration_cast<std::chrono::nanoseconds>(mergeSortfinish - mergeSortstart).count();
    cout << "mergeSort Slorting Time Complaxity: " << mergeSorttime << "ns\n";

    auto selectionSortstart = std::chrono::high_resolution_clock::now();
    selectionSort(arr, size);
    auto selectionSortfinish = std::chrono::high_resolution_clock::now();
    int selectionSorttime = std::chrono::duration_cast<std::chrono::nanoseconds>(selectionSortfinish - selectionSortstart).count();
    cout << "Selection Slorting Time Complaxity: " << selectionSorttime << "ns\n";

    auto bubbleSortstart = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, size);
    auto bubbleSortfinish = std::chrono::high_resolution_clock::now();
    int bubbleSorttime = std::chrono::duration_cast<std::chrono::nanoseconds>(bubbleSortfinish - bubbleSortstart).count();
    cout << "bubble Slorting Time Complaxity: " << bubbleSorttime << "ns\n";

    auto insertionSortstart = std::chrono::high_resolution_clock::now();
    insertionSort(arr, size);
    auto insertionSortfinish = std::chrono::high_resolution_clock::now();
    int insertionSorttime = std::chrono::duration_cast<std::chrono::nanoseconds>(insertionSortfinish - insertionSortstart).count();
    cout << "insertion Slorting Time Complaxity: " << insertionSorttime << "ns\n";

    auto quickSortstart = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    auto quickSortfinish = std::chrono::high_resolution_clock::now();
    int quickSorttime = std::chrono::duration_cast<std::chrono::nanoseconds>(quickSortfinish - quickSortstart).count();
    cout << "quick Slorting Time Complaxity: " << quickSorttime << "ns\n";
}
void searchingArray()
{
    int arr[2000];
    ifstream infile("array.txt");
    for (int i = 0; i < 5; ++i)
    {
        infile >> arr[i];
    }
    infile.close();
    int size = sizeof(arr) / sizeof(arr[0]);

    auto LinearSearchstart = std::chrono::high_resolution_clock::now();
    int result = LinearSearch(arr, size, 80);
    auto LinearSearchfinish = std::chrono::high_resolution_clock::now();
    int LinearSearchtime = std::chrono::duration_cast<std::chrono::nanoseconds>(LinearSearchfinish - LinearSearchstart).count();
    cout << "LinearSearch Time Complaxity: " << LinearSearchtime << "ns\n";

    auto sbinarySearchstart = std::chrono::high_resolution_clock::now();
    int result1 = binarySearch(arr, 0, size - 1, 80);
    auto binarySearchfinish = std::chrono::high_resolution_clock::now();
    int binarySearchtime = std::chrono::duration_cast<std::chrono::nanoseconds>(binarySearchfinish - sbinarySearchstart).count();
    cout << "binarySearch Time Complaxity: " << binarySearchtime << "ns\n";
}
void admin()
{
    while (1)
    {
        cout << "\n\t\t\t==============================\n";
        cout << "\n\t\t\t     WELCOME TO BEST SORTING ALGOTOM PROOF  \n";
        cout << "\n\t\t\t==============================\n\n";
        cout << "\n\t\t\t* * * * * * * * * * * * * * * *\n";
        cout << "\n\t\t\t1. Enter The Array.\n\n\t\t\t2. Sorting Proof\n\n\t\t\t3. Searching Proff\n\n\t\t\t4. Exit\n";
        cout << "\n\n\t\t\tSelect your choice\n";
        int u;
        cin >> u;
        if (u == 1)
        {
            int arr[] = {2000,
                         1999,
                         1998,
                         1997,
                         1996,
                         1995,
                         1994,
                         1993,
                         1992,
                         1991,
                         1990,
                         1989,
                         1988,
                         1987,
                         1986,
                         1985,
                         1984,
                         1983,
                         1982,
                         1981,
                         1980,
                         1979,
                         1978,
                         1977,
                         1976,
                         1975,
                         1974,
                         1973,
                         1972,
                         1971,
                         1970,
                         1969,
                         1968,
                         1967,
                         1966,
                         1965,
                         1964,
                         1963,
                         1962,
                         1961,
                         1960,
                         1959,
                         1958,
                         1957,
                         1956,
                         1955,
                         1954,
                         1953,
                         1952,
                         1951,
                         1950,
                         1949,
                         1948,
                         1947,
                         1946,
                         1945,
                         1944,
                         1943,
                         1942,
                         1941,
                         1940,
                         1939,
                         1938,
                         1937,
                         1936,
                         1935,
                         1934,
                         1933,
                         1932,
                         1931,
                         1930,
                         1929,
                         1928,
                         1927,
                         1926,
                         1925,
                         1924,
                         1923,
                         1922,
                         1921,
                         1920,
                         1919,
                         1918,
                         1917,
                         1916,
                         1915,
                         1914,
                         1913,
                         1912,
                         1911,
                         1910,
                         1909,
                         1908,
                         1907,
                         1906,
                         1905,
                         1904,
                         1903,
                         1902,
                         1901,
                         1900,
                         1899,
                         1898,
                         1897,
                         1896,
                         1895,
                         1894,
                         1893,
                         1892,
                         1891,
                         1890,
                         1889,
                         1888,
                         1887,
                         1886,
                         1885,
                         1884,
                         1883,
                         1882,
                         1881,
                         1880,
                         1879,
                         1878,
                         1877,
                         1876,
                         1875,
                         1874,
                         1873,
                         1872,
                         1871,
                         1870,
                         1869,
                         1868,
                         1867,
                         1866,
                         1865,
                         1864,
                         1863,
                         1862,
                         1861,
                         1860,
                         1859,
                         1858,
                         1857,
                         1856,
                         1855,
                         1854,
                         1853,
                         1852,
                         1851,
                         1850,
                         1849,
                         1848,
                         1847,
                         1846,
                         1845,
                         1844,
                         1843,
                         1842,
                         1841,
                         1840,
                         1839,
                         1838,
                         1837,
                         1836,
                         1835,
                         1834,
                         1833,
                         1832,
                         1831,
                         1830,
                         1829,
                         1828,
                         1827,
                         1826,
                         1825,
                         1824,
                         1823,
                         1822,
                         1821,
                         1820,
                         1819,
                         1818,
                         1817,
                         1816,
                         1815,
                         1814,
                         1813,
                         1812,
                         1811,
                         1810,
                         1809,
                         1808,
                         1807,
                         1806,
                         1805,
                         1804,
                         1803,
                         1802,
                         1801,
                         1800,
                         1799,
                         1798,
                         1797,
                         1796,
                         1795,
                         1794,
                         1793,
                         1792,
                         1791,
                         1790,
                         1789,
                         1788,
                         1787,
                         1786,
                         1785,
                         1784,
                         1783,
                         1782,
                         1781,
                         1780,
                         1779,
                         1778,
                         1777,
                         1776,
                         1775,
                         1774,
                         1773,
                         1772,
                         1771,
                         1770,
                         1769,
                         1768,
                         1767,
                         1766,
                         1765,
                         1764,
                         1763,
                         1762,
                         1761,
                         1760,
                         1759,
                         1758,
                         1757,
                         1756,
                         1755,
                         1754,
                         1753,
                         1752,
                         1751,
                         1750,
                         1749,
                         1748,
                         1747,
                         1746,
                         1745,
                         1744,
                         1743,
                         1742,
                         1741,
                         1740,
                         1739,
                         1738,
                         1737,
                         1736,
                         1735,
                         1734,
                         1733,
                         1732,
                         1731,
                         1730,
                         1729,
                         1728,
                         1727,
                         1726,
                         1725,
                         1724,
                         1723,
                         1722,
                         1721,
                         1720,
                         1719,
                         1718,
                         1717,
                         1716,
                         1715,
                         1714,
                         1713,
                         1712,
                         1711,
                         1710,
                         1709,
                         1708,
                         1707,
                         1706,
                         1705,
                         1704,
                         1703,
                         1702,
                         1701,
                         1700,
                         1699,
                         1698,
                         1697,
                         1696,
                         1695,
                         1694,
                         1693,
                         1692,
                         1691,
                         1690,
                         1689,
                         1688,
                         1687,
                         1686,
                         1685,
                         1684,
                         1683,
                         1682,
                         1681,
                         1680,
                         1679,
                         1678,
                         1677,
                         1676,
                         1675,
                         1674,
                         1673,
                         1672,
                         1671,
                         1670,
                         1669,
                         1668,
                         1667,
                         1666,
                         1665,
                         1664,
                         1663,
                         1662,
                         1661,
                         1660,
                         1659,
                         1658,
                         1657,
                         1656,
                         1655,
                         1654,
                         1653,
                         1652,
                         1651,
                         1650,
                         1649,
                         1648,
                         1647,
                         1646,
                         1645,
                         1644,
                         1643,
                         1642,
                         1641,
                         1640,
                         1639,
                         1638,
                         1637,
                         1636,
                         1635,
                         1634,
                         1633,
                         1632,
                         1631,
                         1630,
                         1629,
                         1628,
                         1627,
                         1626,
                         1625,
                         1624,
                         1623,
                         1622,
                         1621,
                         1620,
                         1619,
                         1618,
                         1617,
                         1616,
                         1615,
                         1614,
                         1613,
                         1612,
                         1611,
                         1610,
                         1609,
                         1608,
                         1607,
                         1606,
                         1605,
                         1604,
                         1603,
                         1602,
                         1601,
                         1600,
                         1599,
                         1598,
                         1597,
                         1596,
                         1595,
                         1594,
                         1593,
                         1592,
                         1591,
                         1590,
                         1589,
                         1588,
                         1587,
                         1586,
                         1585,
                         1584,
                         1583,
                         1582,
                         1581,
                         1580,
                         1579,
                         1578,
                         1577,
                         1576,
                         1575,
                         1574,
                         1573,
                         1572,
                         1571,
                         1570,
                         1569,
                         1568,
                         1567,
                         1566,
                         1565,
                         1564,
                         1563,
                         1562,
                         1561,
                         1560,
                         1559,
                         1558,
                         1557,
                         1556,
                         1555,
                         1554,
                         1553,
                         1552,
                         1551,
                         1550,
                         1549,
                         1548,
                         1547,
                         1546,
                         1545,
                         1544,
                         1543,
                         1542,
                         1541,
                         1540,
                         1539,
                         1538,
                         1537,
                         1536,
                         1535,
                         1534,
                         1533,
                         1532,
                         1531,
                         1530,
                         1529,
                         1528,
                         1527,
                         1526,
                         1525,
                         1524,
                         1523,
                         1522,
                         1521,
                         1520,
                         1519,
                         1518,
                         1517,
                         1516,
                         1515,
                         1514,
                         1513,
                         1512,
                         1511,
                         1510,
                         1509,
                         1508,
                         1507,
                         1506,
                         1505,
                         1504,
                         1503,
                         1502,
                         1501,
                         1500,
                         1499,
                         1498,
                         1497,
                         1496,
                         1495,
                         1494,
                         1493,
                         1492,
                         1491,
                         1490,
                         1489,
                         1488,
                         1487,
                         1486,
                         1485,
                         1484,
                         1483,
                         1482,
                         1481};

            int size = sizeof(arr) / sizeof(arr[0]);
            ofstream outfile("array.txt");
            if (!outfile.is_open())
            {
                cerr << "Failed to open file for writing.\n";
            }

            // Writing the array elements to the file
            for (int i = 0; i < size; ++i)
            {
                outfile << arr[i] << " ";
            }

            // Closing the file
            outfile.close();
            break;
        }
        else if (u == 2)
        {
            sortingArray();
        }
        else if (u == 3)
        {
            searchingArray();
        }
        else if (u == 4)
        {
            break;
        }
        else
            cout << "Invalid option. Please select one of the available options\n";
    }
}

int main()
{
    int ch;
    char username[20];
    char password[20];
    char pwd[20];
    while (5)
    {
        cout << "\n \t\t\t=========================\n";
        cout << "\n\t\t\tWELCOME TO MY SHOP  \n";
        cout << "\n \t\t\t=========================\n\n";
        cout << "\n \t\t\t* * * * * * * * * * * * ";
        cout << "\n\t\t\t  1. ENTER SYSTEM";
        cout << "\n\t\t\t  2. EXIT";
        cout << "\n\t\t\t* * * * * * * * * * * *\n";
        cout << "\n\t\t\t Enter Your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            admin();
            break;
        case 2:
            exit(0);
            break;
        default:
            cout << "Enter valid choice\n";
            break;
        }
    }
    return 0;
}
