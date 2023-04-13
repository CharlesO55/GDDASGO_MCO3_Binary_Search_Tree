#include "bst.h"


#include "timer.h"
#include "csvGenerator.h"

#define NUMBER_OF_TESTS 5      //Number of times to repeat. Creates x amount of Trees
#define SAMPLE_SIZE 1000          //Number of elements/nodes to populate a tree with

#define MIN_RANGE 1     //Minimum RNG value
#define MAX_RANGE 100   //Max RNG value

#define WIPE_CSV 0      //Turn off to store data properly in csv file

double getAverage(double aTimes[]){
    double dTotal = 0;
    for (int i = 0; i < NUMBER_OF_TESTS; i++){
        dTotal += aTimes[i];
    }
    return dTotal / NUMBER_OF_TESTS;
}



int nExternCounter = 0;     //Global External counter since can't insert pointers to function prototypes


int main(){
    if (WIPE_CSV == 1){
        resetCSV();
    }
    struct timespec sBegin, sEnd;

    double aPreorderTime[NUMBER_OF_TESTS];
    double aInorderTime[NUMBER_OF_TESTS];
    double aPostorderTime[NUMBER_OF_TESTS];
    double aMinFind[NUMBER_OF_TESTS];
    double aMaxFind[NUMBER_OF_TESTS];
    double aTotalCounter[5] = {0,0,0,0,0};

    //Repeat for number of tests
    for (int i = 0; i < NUMBER_OF_TESTS; i++){
        bst *pTree = create();
        
        //Populate with randoms
        for (int j = 0; j < SAMPLE_SIZE; j++){
            insert(pTree, rand() % (MAX_RANGE + MIN_RANGE - 1) + MIN_RANGE);    
        }

        //Preorder
        sBegin = getTime();
        printf("\nPREODER   : "); preorder(pTree->pRoot);
        sEnd = getTime();
        aPreorderTime[i] = getElapsed(sBegin, sEnd) * 1000; //Convert to ms
        aTotalCounter[0] += nExternCounter;
        nExternCounter = 0;

        //Inorder
        sBegin = getTime();
        printf("\nINORDER   : "); inorder(pTree->pRoot);
        sEnd = getTime();
        aInorderTime[i] = getElapsed(sBegin, sEnd) * 1000; //Convert to ms
        aTotalCounter[1] += nExternCounter;
        nExternCounter = 0;

        //Postorder
        sBegin = getTime();
        printf("\nPOSTODER  : "); postorder(pTree->pRoot);
        sEnd = getTime();
        aPostorderTime[i] = getElapsed(sBegin, sEnd) * 1000; //Convert to ms
        aTotalCounter[2] += nExternCounter;
        nExternCounter = 0;

        //Min
        sBegin = getTime();
        printf("\nMIN: %d", minimum(pTree->pRoot)->data);
        sEnd = getTime();
        aMinFind[i] = getElapsed(sBegin, sEnd) * 1000;
        aTotalCounter[3] += nExternCounter;
        nExternCounter = 0;
        //Max
        sBegin = getTime();
        printf("\nMAX: %d", maximum(pTree->pRoot)->data);
        sEnd = getTime();
        aMaxFind[i] = getElapsed(sBegin, sEnd) * 1000;
        aTotalCounter[4] += nExternCounter;
        nExternCounter = 0;

        free(pTree);
    }
    printf("\nAVERAGES\n");
    double aAvgTime[5] = {
        getAverage(aPreorderTime),
        getAverage(aInorderTime),
        getAverage(aPostorderTime),
        getAverage(aMinFind),
        getAverage(aMaxFind)
    };

    char str_Mode[5][20] = {"PREODER", "INORDER", "POSTORDER", "MIN", "MAX"};
    for (int i = 0; i < NUMBER_OF_TESTS; i++){
        aTotalCounter[i] = aTotalCounter[i] / NUMBER_OF_TESTS;
        printf("\n%s: %f, %f", str_Mode[i], aAvgTime[i], aTotalCounter[i]);
        recordCSV(SAMPLE_SIZE, str_Mode[i], aAvgTime[i], aTotalCounter[i]);
    }


    /*
    bst *pTree = create();
    {
    insert(pTree, 7);
    }
    insert(pTree, 3);
    insert(pTree, 1);
    insert(pTree, 2);
    insert(pTree, 4);
    insert(pTree, 9);
    insert(pTree, 8);
    insert(pTree, 16);
    insert(pTree, 10);
    insert(pTree, 14);*/
  /*  int nTarget = 7;


    printf("\nPREODER   : "); preorder(pTree->pRoot);
    printf("\nINORDER   : "); inorder(pTree->pRoot);
    printf("\nPOSTORDER : "); postorder(pTree->pRoot);
    printf("\nMIN: %d", minimum(pTree->pRoot)->data);
    printf("\nMAX: %d", maximum(pTree->pRoot)->data);
    printf("\nPREDECESSOR OF %d : %d", nTarget, predecessor(pTree, nTarget)->data);
    printf("\nSUCCESSOR OF %d   : %d", nTarget, successor(pTree, nTarget)->data);
*/
    printf("\nclosing program...");
}