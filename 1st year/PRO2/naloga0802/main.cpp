#include <iostream>


//https://appdividend.com/2019/05/31/c-templates-tutorial-with-example-template-class-in-c/
template < typename T, typename U>
void sum(T a[],int n,U b[],int m)
{
    // two different types of array can be passed
    T sum_type1 = 0;
    int i;
    for(i=0;i<n;i++)
        sum_type1 += a[i];

    std::cout << "Sum of Array of Type 1 : " << sum_type1 << "\n";

    U sum_type2 =0;
    for(i=0;i<m;i++)
        sum_type2 += b[i];
    std::cout << "Sum of Array of Type 2 : " << sum_type2 << "\n";
}

//https://www.ibm.com/docs/en/zos/2.4.0?topic=only-function-templates-c
template<class T>
void quicksort(T a[], const int& leftarg, const int& rightarg)
{
    if (leftarg < rightarg) {

        T pivotvalue = a[leftarg];
        int left = leftarg - 1;
        int right = rightarg + 1;

        for(;;) {

            while (a[--right] > pivotvalue);
            while (a[++left] < pivotvalue);

            if (left >= right) break;

            T temp = a[right];
            a[right] = a[left];
            a[left] = temp;
        }

        int pivot = right;
        quicksort(a, leftarg, pivot);
        quicksort(a, pivot + 1, rightarg);
    }
}

//https://classes.mst.edu/compsci1570/templates.htm
template <typename T>
void swap ( T & t1, T & t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
    return;
}

//----------
template<typename T, typename T2>
T changeTo(T2 b){

}

int main() {

}
