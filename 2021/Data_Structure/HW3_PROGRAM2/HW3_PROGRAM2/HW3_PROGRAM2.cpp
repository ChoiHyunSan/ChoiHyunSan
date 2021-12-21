#pragma warning(disable : 4996)
#include <iostream>

using namespace std;

typedef struct node {
    char* data;
    node* prev;
    node* next;
}Node;

#define MAX_LIST 10

Node* create_node(char* p);//
Node* add_node(Node* head, char* p);//
Node* delete_node(Node* head, Node* p);
bool is_in_list(Node* head, char* str);//
int count_list(Node* head);//
bool _is_empty(Node* head);//
void print_list(Node* head);//
Node* search(Node* head, char* str);//


bool compare(char*str1 , char *str2) {
    for (int i = 0; i < strlen(str1); i++) {
        if ((str1)[i] != str2[i])
            return false;
    }
    return true;
}
Node* search(Node* head, char* str) {
    if (_is_empty(head) == true)
        return NULL;
    if(compare(head->next->data, str) == true)
        return head->next;
    else if (head->next->data != str)
        search(head->next, str);

}

bool is_in_list(Node* head, char* str) {
    if (_is_empty(head) == true)
        return false;
    if (head->next->data == NULL)
        return false;
    else if (compare(head->next->data, str) == true)
        return true;
    else if (head->next->next == NULL)
        return false;
    else
        is_in_list(head->next, str);
}

int count_list(Node* head) {
    if (_is_empty(head) == false) {
        if (head->next->next == NULL)
            return 1;
        else
            return count_list(head->next) + 1;
    }
    else if (_is_empty(head) == true)
        return 0;
}
Node* create_node(char* p) {
    Node* temp = NULL;
    temp = (Node*)malloc(sizeof(Node));

    char* pp = (char*)malloc(sizeof(p));

    if (temp == NULL || pp == NULL) {
        cout << "동적할당 실패" << endl;
        exit(1);
    }
    
    strcpy(pp, p);

    temp->data = pp;
    temp->prev = NULL;
    temp->next = NULL;

    return temp;
}

Node* add_node(Node* head, char* p) {
    Node* temp = NULL;
    
    temp = (Node*)create_node(p);

    temp->prev = head;

    temp->next = head->next;

    head->next->prev = temp;

    head->next = temp;

    return head;
}

bool _is_empty(Node* head) {
    if (head->next->next == NULL)
        return true;
    else
        return false;
}

Node* delete_node(Node* head, int p) {

    Node* temp = head;

    //리스트가 비어있는지 확인
    if (_is_empty(head) == true) {
        cout << "제거할 노드를 찾을 수 없습니다" << endl;
        return head;
    }

    for (int i = 0; i < p; i++) {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);

    return head;
}

void print_list(Node* head) {

    Node* p = head->next;
    int count = 1;
    
    if (p->next == NULL) {
        printf("List is empty!!\n");
        exit(1);
    }

    while (p->next != NULL) {
        printf("%d) %s ", count,p->data);
        p = p->next;
        count++;
    }
    printf("\n");

    return;
}



int main()
{
    Node header, trailer;
    Node* head;

        header.prev = NULL;
        header.next = &trailer;
        trailer.prev = &header;
        trailer.next = NULL;

        head = &header;

    int i = 0;
    while (i == 0) {

        int temp = 0;       
        char str[100] = {};
        Node* delete_l = NULL;
        int delete_list = 0;

        cout << "choose one : 1) add 2) delete 3) is_in_list 4) count_list 5) is_empty 6)search 7) exit" << endl;
        cin >> temp;

        temp += 48;

        switch (temp) {
        case '1':
            cout << "최근 실행한 앱 이름을 입력하시오 : ";
            cin >> str;
            head = add_node(head, str);
            print_list(head);
            break;
        case '2':
            cout << "지우고 싶은 앱의 번호를 선택하세요 : ";
            cin >> delete_list;
            head = delete_node(head, delete_list);
            print_list(head);
            break;
        case '3':
            cout << "리스트에 있는지 확인하고 싶은 앱 이름을 입력하시오 : ";
            cin >> str;
            if (is_in_list(head, str) == true)
                cout << "리스트 안에 " << str << "은 존재합니다" << endl;
            else
                cout << "리스트 안에 " << str << "은 존재하지 않습니다" << endl;
            break;
        case '4':
            cout << "리스트 안의 노드의 개수를 출력합니다.. " << endl;
            cout << "리스트 안의 노드의 개수는 " << count_list(head) << "개 입니다" << endl;
            break;
        case '5':
            cout << "리스트가 비어있는지 확인중입니다..  " << endl;
            if (_is_empty(head) == true)
                cout << "리스트는 비어있습니다" << endl;
            else
                cout << "리스트는 비어있지 않습니다" << endl;
            break;
        case '6':
            cout << "찾고 싶은 앱의 이름을 입력하세요" << endl;
            cin >> str;
            if (search(head, str) == NULL)
                cout << "일치하는 앱이 없습니다." << endl;
            else
                cout << "해당 노드의 주소는 " << search(head, str) << "입니다" << endl;
            break;
        case '7':
            cout << "테스트를 종료합니다..  " << endl;
            i++;
            break;
        }

    }
    return 0;
 
}


