#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node *next;
    Node *prev;
};

Node* createNode(int coef, int exp) {
    Node *s = new Node;
    s -> coef = coef;
    s -> exp = exp;
    s -> next = NULL;
    s->prev = NULL;
    return s;
}

void addNode(int coef, int exp,Node** head,Node **tail){
    Node *newNode = createNode(coef,exp);
    if(*head == NULL){
        *head = newNode;
        *tail = newNode;
        return;
    }
    (*tail) -> next = newNode;
    newNode -> prev = *tail;
    *tail = newNode;
}

Node* addpolynomial(Node** head1,Node** head2) {
    Node *temp1 = *head1;
    Node *temp2 = *head2;
    Node *headresult = NULL;
    Node *tailresult = NULL;

    while(temp1 != NULL && temp2 != NULL) {
        if(temp1 -> exp == temp2 -> exp) {
            int coef = temp1->coef + temp2->coef;
            if(coef != 0) {
                addNode(coef, temp1->exp, &headresult,&tailresult);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1 -> exp > temp2 -> exp) {
            addNode(temp1 -> coef,temp1 -> exp,&headresult,&tailresult);
            temp1 = temp1 -> next;
        }
        else if(temp1 -> exp < temp2 -> exp) {
            addNode(temp2 -> coef,temp2 -> exp,&headresult,&tailresult);
            temp2 = temp2 -> next;
        }
    }
    while(temp1 != NULL) {
        addNode(temp1->coef, temp1->exp, &headresult,&tailresult);
        temp1 = temp1->next;
    }
    while(temp2 != NULL) {
        addNode(temp2->coef, temp2->exp, &headresult,&tailresult);
        temp2 = temp2->next;
    }

    return headresult;
}

Node* multiplypolynomial(Node** head1,Node** head2) {
    Node *temp1 = *head1;
    Node *headresult = NULL;
    Node *tailresult = NULL;
    vector<int> coef(100,0);

    while(temp1 != NULL) {
        Node *temp2 = *head2;
        while(temp2 != NULL) {
           coef[temp1->exp + temp2->exp] += temp1->coef * temp2->coef;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    for(int i = coef.size()-1; i >= 0; i--) {
        if(coef[i] != 0) {
            addNode(coef[i],i,&headresult,&tailresult);
        }
    }

    return headresult;
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* tail1 = NULL;
    Node* tail2 = NULL;
    addNode(2,5,&head1,&tail1);
    addNode(4,3,&head1,&tail1);
    addNode(3,2,&head1,&tail1);
    addNode(5,0,&head1,&tail1);

    addNode(3,5,&head2,&tail2);
    addNode(5,3,&head2,&tail2);
    addNode(4,2,&head2,&tail2);
    addNode(6,0,&head2,&tail2);
    cout  << endl;
    // Node* addresult = addpolynomial(&head1,&head2);
    // Node* addtemp = addresult;
    // while(addtemp != NULL) {
    //     cout << addtemp -> coef << "x" << addtemp -> exp << " ";
    //     addtemp = addtemp->next;
    // }
    // cout << endl;
    Node* mulresult = multiplypolynomial(&head1,&head2);
    Node* multemp = mulresult;
    while(multemp != NULL) {
        cout << multemp -> coef << "x" << multemp -> exp << " ";
        multemp = multemp->next;
    }
    return 0;
}