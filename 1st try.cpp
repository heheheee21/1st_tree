#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

struct knot//структура дерева
{ 
    string animal_guess = "";//если это конечный узел, то поле буде не пустое
    string question = "";
    knot* yesnode = nullptr;//указатели на ветки
    knot* nonode = nullptr;
};

void new_inf(string& question, string& animal)
{
    cout << "Какое животное вы хотели загадать? " << endl;
    cin >> animal;

    cin.ignore();

    cout << "Какой вопрос можно было бы зада? ";
    getline(cin, question);
}

void person_answer(string& answer)
{
    cin >> answer;
    while (answer != "да" && answer != "нет")
    {
        cout << "переделывай: ";
        cin >> answer;
    }
}

void new_branch(knot* current_branch, string &answer)
{
    string new_question, new_animal_guess;
    cout << "Вы загадали животное " <<  "- " << current_branch->animal_guess << "?" << endl;
    person_answer(answer);
    if (answer == "да")
    {
        cout << "Комп угадал ура" << endl;
    }
    else
    {
        new_inf(new_question, new_animal_guess);
        knot* yesnode = new knot;
        knot* nonode = new knot;
        yesnode->animal_guess = new_animal_guess;
        nonode->animal_guess = current_branch->animal_guess;
        current_branch->question = new_question;
        current_branch->animal_guess = "";
        current_branch->yesnode = yesnode;
        current_branch->nonode = nonode;
    }
}

void game(knot* current_branch)
{
    string answer;
    if (current_branch->question != "")
    {
        cout << current_branch->question << endl;
        person_answer(answer);
        if (answer == "да")
            game(current_branch->yesnode);
        if (answer == "нет")
            game(current_branch->nonode);
    }
    else
        new_branch(current_branch, answer);
}

bool game_continue()
{
    string otvet;
    cout << "Хотите ли вы продолжить игру с новым деревом? ";
    cin >> otvet;
    if (otvet == "да")
        return 1;
    else
        return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    knot* uzel = new knot;
    uzel->animal_guess = "волчара";
    do
    {
        game(uzel);
    } 
    while (game_continue());

    return 0;

}