
///1. 단순 연결 리스트(Singly LInked List)를 이용하여 숫자들을 항상 정렬된 상태로 유지하는 리스트 SortedList
///를 구현한다.기능으로서 아래 함수들을 구현한 후, 간단한 테스트 함수(main function)를 만들어 테스트 하시오
///(단, 정렬은 오름차순을 기준함) : [70 pt]

///add_node(Node* head, int item) : 정렬된 리스트에 새로운 요소 추가
///delete_node(Node* head, int item) : 정렬된 리스트에서 item 제거
///clear(Node* head) : 리스트의 모든 아이템 삭제
///is_in_list(Node* head, int item) : item이 리스트 안에 있는지를 검사하여, 있으면 TRUE(1)를 리턴하고 없으면 FALSE(0)를 반환
///count_list(Node* head) : 리스트 내의 노드 개수(즉, 아이템 개수)를 반환
///is_empty(Node* head) : 리스트가 비었는지를 검사하여, 비었으면 TRUE(1)를 반환하고 아이템이 존재하면 FALSE(0)를 반환
///print_list(Node* head) : 리스트의 모든 데이터 값을 모니터에 출력

///Note 1) 테스트 함수는 무한 루프를 이용하여 위의 함수들을 메뉴(예: 1. Add; 2. Delete; 3. Clear; …) 를 이용
///해 테스트하는 프로그램을 작성함.
///Note 2) 단순 연결 리스트의 노드는 아래와 같은 구조를 이용하며, 구현 용이성을 위해 dummy 노드 가능함.또
///한, 필요시 함수명과 패러미터를 변경해도 괜찮음.
 
///typedef struct node {
///    int data;
///    struct node* link;
///} Node;

#include <iostream>
 
using namespace std;

typedef struct node {
    int data;
    struct node* link;
}Node;

int count_list(Node* head);
void print_list(Node* head);
bool is_in_item(Node* head, int item);

Node* create_node(int item) {
    Node *temp = NULL;

    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("동적할당 실패");
        exit(1);
    }

    temp->data = item;
    temp->link = NULL;

    return temp;
    
}

/// 리스트를 정렬해주는 함수
void sort(Node* head) {
    //리스트가 비어있는지 확인
    if (head == NULL)
        printf("리스트 내의 item이 존재하지 않습니다. \n");

    int temp = 0;
    node* n_temp;

    //head의 주소값을 저장하고있는 n_temp 생성
    n_temp = head;
    //리스트의 개수만큼 반복문을 이용하여 버블정렬 시행
    for (int i = 0; i < count_list(head); i++) {
        for (int j = 0; j < count_list(head) - i; j++) {
            // head-> data와 head->link->data의 값을 비교하여 head->data가 더 클 경우 두 리스트의 data값을 교환
            if (n_temp->link == NULL)
                break;
            if (n_temp->data > n_temp->link->data) {
                temp = n_temp->data;
                n_temp->data = n_temp->link->data;
                n_temp->link->data = temp;
            }
            // 변환 후 , 그 다음 리스트로 넘어간다.
            n_temp = n_temp->link;
        }
    }
}
///add_node(Node* head, int item) : 정렬된 리스트에 새로운 요소 추가
Node* add_node(Node* head,  int item) {
    Node* temp = NULL;

    temp = create_node(item);
    if (temp != NULL) { 
        
        temp->link = head;

        head = temp;
    }
    sort(head);
    //print_list(head);
    return head;
}

///delete_node(Node* head, int item) : 정렬된 리스트에서 item 제거
Node* delete_node(Node* head, Node* pre, int item) {

    Node* temp = head;
    if (temp == NULL) {
        printf("비어있는 노드 \n");
    }
    if (temp->data == item) {
        if (pre != NULL) {
            pre->link = temp->link;
            return head;
        }
        else {
            // temp = NULL;
            //free(temp);
            return temp->link;
        }
    }
    else {
        if (temp->link != NULL)
            temp = delete_node(temp->link, temp, item);
        else if (temp->link == NULL)
            printf("해당 노드를 찾을 수 없습니다. \n");
    }
    
    sort(head);
    return head;
}

///clear(Node* head) : 리스트의 모든 아이템 삭제
Node* clear(Node* head) {

    Node* temp = NULL;
    //연결된 리스트가 있다면 재귀함수를 이용하여 다음 리스트를 clear
    if (head->link != NULL) {
        temp = clear(head->link);
    }
    //연결된 리스트가 없다면 해당 리스트부터 delete 시작
    if (head->link == NULL) {
        free(head);   
    }
    return temp;
}

///is_in_list(Node* head, int item) : item이 리스트 안에 있는지를 검사하여, 있으면 TRUE(1)를 리턴하고 없으면 FALSE(0)를 반환
bool is_in_item(Node* head, int item) {

    if (head == NULL)
        return false;

    // head의 data가 비어있는지 확인
    if (head->data == NULL)
        return false;

    // head의 data가 item과 같은지 확인
    else if (head->data == item)
        return true;

    // item을 찾지 못한 상태에서 그 다음 리스트가 존재하는지 확인
    else if (head->link == NULL)
        return false;

    // head 가 비어있지도 않고, item과도 같지 않다면 그 다음 리스트의 값을 확인
    else
        is_in_item(head->link, item);
}

///count_list(Node* head) : 리스트 내의 노드 개수(즉, 아이템 개수)를 반환
int count_list(Node* head) {
    // head 가 비어있는지 확인
    if (head != NULL) { 

        // 다음 연결된 리스트가 없다면 1을 반환
        if (head->link == NULL)
            return 1;

        // 다음 연결된 리스트가 있다면 1을 더해주고 재귀함수를 이용하여 해당 head에 연결된 개수 확인
        else
            return count_list(head->link) + 1;
    }
    // head가 비어있다면 0를 반환
    else if (head == NULL) {
        return 0;
    }
}

///is_empty(Node* head) : 리스트가 비었는지를 검사하여, 비었으면 TRUE(1)를 반환하고 아이템이 존재하면 FALSE(0)를 반환
bool _is_empty(Node* head) {
    //head가 비어있는지 확인 ( 비어있을 경우 true 반환)
    if (head == NULL)
        return true;
    //아닐경우 false
    else
        return false;
}

///print_list(Node* head) : 리스트의 모든 데이터 값을 모니터에 출력
void print_list(Node* head) {
  
    Node* p = head;
    if (head == NULL) {
        printf("List is empty!!\n");
    }

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("\n");

    return;
    
}

///Note 1) 테스트 함수는 무한 루프를 이용하여 위의 함수들을 메뉴(예: 1. Add; 2. Delete; 3. Clear; …) 를 이용
///해 테스트하는 프로그램을 작성함.
///Note 2) 단순 연결 리스트의 노드는 아래와 같은 구조를 이용하며, 구현 용이성을 위해 dummy 노드 가능함.또
///한, 필요시 함수명과 패러미터를 변경해도 괜찮음.
void test(Node* head) {
    int i = 0;
    while (i == 0) {

        int temp = 0;

        cout << "choose one : 1) add 2) delete 3) clear 4) is_in_item 5) count_list 6) is_empty 7)exit" << endl;
        cin >> temp;

        temp += 48;

        switch (temp) {
        case '1':
            cout << "리스트에 추가할 숫자를 입력하시오 : ";
            cin >> temp;
            head = add_node(head, temp);
            print_list(head);
            break;
        case '2':
            cout << "리스트에서 제거할 숫자를 입력하시오 : ";
            cin >> temp;
            head = delete_node(head, NULL, temp);
            print_list(head);
            break;
        case '3':
            cout << "리스트를 초기화 합니다.. ";
            head = clear(head);
            print_list(head);
            break;
        case '4':
            cout << "리스트에 있는지 확인하고 싶은 숫자를 입력하시오 : ";
            cin >> temp;
            if (is_in_item(head, temp) == true)
                cout << "리스트 안에 " << temp << "은 존재합니다" << endl;
            else
                cout << "리스트 안에 " << temp << "은 존재하지 않습니다" << endl;
            break;
        case '5':
            cout << "리스트 안의 노드의 개수를 출력합니다.. " << endl;
            cout << "리스트 안의 노드의 개수는 " << count_list(head) << "개 입니다" << endl;
            break;
        case '6':
            cout << "리스트가 비어있는지 확인중입니다..  " << endl;
            if (_is_empty(head) == true)
                cout << "리스트는 비어있습니다" << endl;
            else
                cout << "리스트는 비어있지 않습니다" << endl;
            break;
        case '7':
            cout << "테스트를 종료합니다..  " << endl;
            i++;
            break;
        }

    }
    return;
}
int main()
{
    //단순 연결리스트 생성
    Node *head = NULL;
    //테스트 함수 호출
    test(head);

}

