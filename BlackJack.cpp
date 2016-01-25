#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void cprint(int rand_int) {
    switch(rand_int) {
    case 1 ... 13: cout << "    Spade ";
        switch(rand_int) {
            case 1: cout << "A";
            break;
            case 11: cout << "J";
            break;
            case 12: cout << "Q";
            break;
            case 13: cout << "K";
            break;
            default: cout << rand_int;
        }
        break;
    case 14 ... 26: cout << "    Club ";
        switch(rand_int) {
            case 14: cout << "A";
            break;
            case 24: cout << "J";
            break;
            case 25: cout << "Q";
            break;
            case 26: cout << "K";
            break;
            default: cout << rand_int%13;
        }
        break;
    case 27 ... 39: cout << "    Diamond ";
        switch(rand_int) {
            case 27: cout << "A";
            break;
            case 37: cout << "J";
            break;
            case 38: cout << "Q";
            break;
            case 39: cout << "K";
            break;
            default: cout << rand_int%13;
        }
        break;
    case 40 ... 52: cout << "    Heart ";
        switch(rand_int) {
            case 40: cout << "A";
            break;
            case 50: cout << "J";
            break;
            case 51: cout << "Q";
            break;
            case 52: cout << "K";
            break;
            default: cout << rand_int%13;
        }
        break;
    }
    cout<< "\n";
    return;
}

int rand_card(int card_array[], int r) {
    srand(time(NULL));
    r = rand()% 52+1;
    if (card_array[r] == 0) {
        card_array[r] = 1;
        return r;
    } else {
        while (card_array[r] == 1 ) {
            r = rand()% 52+1;
        }
        card_array[r] = 1;
        return r;
    }
}

int card_point(int r) {
    // if (r<11 && r!=1) {
    //     return r;
    // }
    // int card_num = r%13;
    // if (r == 1 || card_num == 1) {
    //     cout << "You have gotten an Ace. This can either be 1 or 11. Please type '1' or '11'. \n";
    //     int temp;
    //     cin >> temp;
    //     return temp;
    // }
    if (r<11) {
        return r;
    }
    int card_num = r%13;
    switch(card_num) {
        case 11 ... 13: return 10;
        case 0: return 10;
        default: return card_num;
    }
}


int main() {
    int card_array[52] = {0}; //[suit][number]
    int r, i, my_score, deal_score;
    int ace_num = 0;
    my_score = 0;
    deal_score = 0;
    cout << "Here are your two cards:" << endl;
    for(i=0; i<2; i++) { //get 2 cards for player and prints them out
        r = rand_card(card_array, r);
        cprint(r);
        my_score += card_point(r);
        if (r == 1 || r == 14 || r == 27 || r == 40) {
            ace_num += 1;
        }
    }

    cout << "\nThe dealer now gets two cards. One of his cards is: " << endl;
    r = rand_card(card_array,r);
    cprint(r);
    deal_score += card_point(r);
    // cout << "dealer score is " << deal_score << endl;
    r = rand_card(card_array, r);
    // cprint(r); // delete later
    deal_score += card_point(r);
    // cout << "dealer score is " << deal_score << endl; //delete later

    cout << "\nNow you decide your next move. \nEnter HIT to receive another card. \nEnter STAND if you don't want another card. \n \n";

    string move;
    cin >> move;

    while (move == "HIT") {
        // cout << "##" << endl;
        r = rand_card(card_array, r);
        //cout << "r is " << r << "      ";
        cprint(r);
        cout << "\n";
        my_score += card_point(r);
        if (r == 1 || r == 14 || r == 27 || r == 40) {
            ace_num += 1;
        }
        // cout << "my score is " << my_score << endl;
        if (my_score > 21) {
            break;
        }

        if (deal_score < 17) {
            r = rand_card(card_array, r);
            // cprint(r); // delete later
            deal_score += card_point(r);
            // cout << "dealer score is " << deal_score << endl; //delete later
        }
        if (deal_score > 21) {
            cout << "YOU WON" << endl;
            break;
        }
        cin >> move;
    }


    if (deal_score < 17) {
        r = rand_card(card_array, r);
        // cprint(r); // delete later
        deal_score += card_point(r);
        // cout << "dealer score is " << deal_score << endl; //delete later
    }

    for(i=0; i<ace_num; i++) {//    if (ace_num > 1) {
        cout << "Your cards have one Ace. Please type either '1' or '11'.\n";
        int temp;
        cin >> temp;
        if (temp == 11) {
            my_score += 10;
        }
    }

    if (my_score > 21) {
        cout << "\nYour final score is " << my_score << ". \nThis is greater than 21. \nThe dealer's score is " << deal_score<< ".\nYOU LOST";
    } else if (deal_score > 21) {
        cout << "\nThe dealer's score is " << deal_score <<".\n This is greater than 21. \nThe final score is " << my_score<< ".\n YOU WON" << endl;
    } else if (my_score == 21) {
        cout << "\nYour final score was 21. \nThe dealer's score is " << deal_score<< ".\nYOU WON!";
    } else {
        int my_diff = 21-my_score;
        int deal_diff = 21-deal_score;
        if (my_diff <= deal_diff) {
            cout << "\nYour final score was " << my_score << "\nThe dealer's final score was " << deal_score << "\nYOU WON" ;
        } else {
            cout << "\nYour final score was " << my_score << "\nThe dealer's final score was " << deal_score << "\nYOU LOST";
        }
    }

}
