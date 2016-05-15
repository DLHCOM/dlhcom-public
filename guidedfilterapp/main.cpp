//
//  main.cpp
//  guidedfilterapp
//
//  Created by yingjian he on 4/29/16.
//  Copyright © 2016 Sophia He. All rights reserved.
//

#include <iostream>
using namespace std;

/* Function to swap two characters */
void swap(char& a, char& b)
{
    char temp;
    temp = a;
    a = b;
    b = temp;
}

/* Function to obtain permutations of string characters */
void permutation(string s,int i,int n)
{
    int j;
    if (i == n)
        cout << s << "\t";
    else
    {
        for (j = i; j < s.length(); j++)
        {
            swap(s[i],s[j]);
            permutation(s, i + 1, n);
            swap(s[i],s[j]);
        }
    }
}


typedef struct _data
{
    struct _data *next;
    int value;
} data;

class Node
{
    Node *next = 0;
    int data;
    Node(int d) {data = d;}
    ~Node();
};
void imresize(unsigned char *inI, unsigned char *origI, float invs, int format, int resize, int size);


int main(int argc, const char * argv[]) {
    string s;
    // insert code here...
    cout << "Hello, World!\n";
    
    cout << "Enter the string : ";
    cin >> s;
    cout << endl << "The permutations of the given string : " << endl;
    permutation(s, 0, s.length() - 1);
    cout << endl;
    
    return 0;
}

int BinarySearch(int* array, int lower, int upper, int target);

int BinarySearch(int* array, int lower, int upper, int target)
{
    int middle = (lower+upper)/2;
    if (array == 0)
        return -1;
    if (middle == upper && array[middle] != target)
        return target;
    else if (array[middle] > target )
        return BinarySearch(array,lower,middle-1,target);
    else if (array[middle]<target)
        return BinarySearch(array, middle+1,upper, target);
    else
        return middle;
}

int fastguidedfilter(unsigned char *I, unsigned char *p, int r, int eps, int s, int imagesize)
{
#if 0
    %   GUIDEDFILTER   O(1) time implementation of guided filter.
    %
    %   - guidance image: I (should be a gray-scale/single channel image)
    %   - filtering input image: p (should be a gray-scale/single channel image)
    %   - local window radius: r
    %   - regularization parameter: eps
    %   - subsampling ratio: s (try s = r/4 to s=r)
    
    I_sub = imresize(I, 1/s, 'nearest'); % NN is often enough
    p_sub = imresize(p, 1/s, 'nearest');
    r_sub = r / s; % make sure this is an integer
    
    [hei, wid] = size(I_sub);
    N = boxfilter(ones(hei, wid), r_sub); % the size of each local patch; N=(2r+1)^2 except for boundary pixels.
        
        mean_I = boxfilter(I_sub, r_sub) ./ N;
    mean_p = boxfilter(p_sub, r_sub) ./ N;
    mean_Ip = boxfilter(I_sub.*p_sub, r_sub) ./ N;
    cov_Ip = mean_Ip - mean_I .* mean_p; % this is the covariance of (I, p) in each local patch.
    
    mean_II = boxfilter(I_sub.*I_sub, r_sub) ./ N;
    var_I = mean_II - mean_I .* mean_I;
    
    a = cov_Ip ./ (var_I + eps);
    b = mean_p - a .* mean_I;
    
    mean_a = boxfilter(a, r_sub) ./ N;
    mean_b = boxfilter(b, r_sub) ./ N;
    
    mean_a = imresize(mean_a, [size(I, 1), size(I, 2)], 'bilinear'); % bilinear is recommended
    mean_b = imresize(mean_b, [size(I, 1), size(I, 2)], 'bilinear');
    
    q = mean_a .* I + mean_b;
    end
#else
    int i;
    int imageresize = imagesize;
    unsigned char I_sub[imageresize]; //% NN is often enough
    unsigned char p_sub[imageresize];
    int r_sub = r / s; //% make sure this is an integer
    imresize(I_sub,I, 1/s, 0, imageresize,imagesize); //% NN is often enough
    imresize(p_sub, p, 1/s, 0, imageresize,imagesize);
    
    for (i=0;i<imageresize;i++)
    {
        printf("I_sub[%d]: %x p_sub[%d]: %x\n",i,I_sub[i],i, p_sub[i]);
    }
    return 0;
#endif
    
}

void imresize(unsigned char *inI, unsigned char *origI, float invs, int format, int resize, int size)
{
    int index;
    for (index=0;index<resize;index++)
    {
        inI[index] = origI[index];
    }
}

void boxfilter(unsigned char *imgsrc, unsigned char *imgdst, int r, int size)
{
#if 0
    function imDst = boxfilter(imSrc, r)
    
    %   BOXFILTER   O(1) time box filtering using cumulative sum
    %
    %   - Definition imDst(x, y)=sum(sum(imSrc(x-r:x+r,y-r:y+r)));
    %   - Running time independent of r;
    %   - Equivalent to the function: colfilt(imSrc, [2*r+1, 2*r+1], 'sliding', @sum);
    %   - But much faster.
    
    [hei, wid] = size(imSrc);
    imDst = zeros(size(imSrc));
    
    %cumulative sum over Y axis
    imCum = cumsum(imSrc, 1);
    %difference over Y axis
    imDst(1:r+1, :) = imCum(1+r:2*r+1, :);
    imDst(r+2:hei-r, :) = imCum(2*r+2:hei, :) - imCum(1:hei-2*r-1, :);
    imDst(hei-r+1:hei, :) = repmat(imCum(hei, :), [r, 1]) - imCum(hei-2*r:hei-r-1, :);
    
    %cumulative sum over X axis
    imCum = cumsum(imDst, 2);
    %difference over Y axis
    imDst(:, 1:r+1) = imCum(:, 1+r:2*r+1);
    imDst(:, r+2:wid-r) = imCum(:, 2*r+2:wid) - imCum(:, 1:wid-2*r-1);
    imDst(:, wid-r+1:wid) = repmat(imCum(:, wid), [1, r]) - imCum(:, wid-2*r:wid-r-1);
    end
#else
    
#endif
}