#include <bits/stdc++.h>

using namespace std;

long lenght, height, StLenght;
vector<int> Stvector;
vector<int> arrayInput = {2, 7, 3, 8};

vector<int> createST(vector<int> array)
{
    lenght = array.size();
    height = ceil(log2(lenght));
    StLenght = 2 * pow(2, height) - 1;
    return vector<int>(StLenght);
}

int fillSt(int currentIndex, int startIndex, int endIndex)
{

    if (startIndex == endIndex)
    {
        Stvector.at(currentIndex) = arrayInput.at(startIndex);
        return arrayInput.at(startIndex);
    }

    int leftChildIndex = 2 * currentIndex + 1;
    int rightChildInput = 2 * currentIndex + 2;
    int midIndex = (startIndex + endIndex) / 2;

    int minLeft = fillSt(leftChildIndex, startIndex, midIndex);
    int minRight = fillSt(rightChildInput, midIndex + 1, endIndex);

    Stvector.at(currentIndex) = min(minLeft, minRight);

    return Stvector.at(currentIndex);
}

int searchMinSt(int l, int r, int currentIndex, int startIndex, int endIndex)
{

    if (l > endIndex || r < startIndex)
    {
        return INT_MAX;
    }

    else if (l <= startIndex && r >= endIndex)
    {
        return Stvector.at(currentIndex);
    }

    else
    {
        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildInput = 2 * currentIndex + 2;
        int midIndex = startIndex + (-startIndex + endIndex) / 2;

        int leftMinVal = searchMinSt(l, r, leftChildIndex, startIndex, midIndex);
        int rightMinVal = searchMinSt(l, r,rightChildInput, midIndex + 1,endIndex);

        return min(leftMinVal,rightMinVal);
    }
}

int updateSt(int currentIndex,int index, int value,int startIndex, int endIndex){
    
    if(startIndex == endIndex){
        if(startIndex == index){
        Stvector.at(currentIndex) = value;
        return value;
        }
        else return Stvector.at(currentIndex);
    }

    else if(index < startIndex || index > endIndex) return Stvector.at(currentIndex);

    else{
        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildInput = 2 * currentIndex + 2;
        int midIndex = (-startIndex + endIndex) / 2;
        
        Stvector.at(currentIndex) = min(updateSt(leftChildIndex, index, value, startIndex, midIndex),
                    updateSt(rightChildInput, index, value, midIndex + 1,endIndex));
        return Stvector.at(currentIndex);
    }

}

int main(int argc, char const *argv[])
{
    Stvector = createST(arrayInput);
    fillSt(0, 0, arrayInput.size() - 1);
    for(auto a : Stvector) cout << a << endl;    
    cout << "===================================" << endl;
    cout << searchMinSt(1,3,0,0,lenght - 1)<<endl;;
    cout << "===================================" << endl;
    updateSt(0,0,9,0,3);
    for (int i = 0; i < Stvector.size(); i++){
        cout << Stvector.at(i) << endl;
    }
    return 0;
}
