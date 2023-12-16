#include "blackjack.h"

Blackjack::Blackjack(bool start) : player_sum(0), dealer_sum(0), player_count(1), dealer_count(1), won(0), played(0)
{
    if (start)
    {
        start_game();
    }
}

void Blackjack::start_game()
{

    for (auto &card : cards)
    { // J Q K nın değerlerini 10 yap
        card.value = (card.number >= 10) ? 10 : card.number;
    }

    system("cls");
    std::cout << "Shuffling the cards";
    for (int i = 0; i < 5; i++)
    {
        std::cout << "." << std::flush;
        Sleep(250);
    }
    shuffle();

    while (true)
    {
        game();

        std::string quit;
        std::cout << "---------------------------" << std::endl;
        std::cout << "\tplayed:\t" << played << "\n\twon:\t" << won << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "|   Quit(-)   |   Go(+)   |" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cin >> quit;

        if (quit == "+")
        {

            player_count = 1;
            player_sum = 0;
            dealer_count = 1;
            dealer_sum = 0;

            if (52 - top < 12)
            { // kalan card sayısını kontrol ediyor
                system("cls");
                std::cout << "Shuffling the cards again";
                for (int i = 0; i < 5; i++)
                {
                    std::cout << "." << std::flush;
                    Sleep(250);
                }
                top = 0;
                shuffle();
            }
        }
        else
        {
            break;
        }
    }
}

void Blackjack::game()
{

    // 1    -> BLACKJACK
    // 0    -> NO PROBLEM
    // -1   -> BUSTED

    system("cls");
    deal_cards();

    while (true)
    {
        system("cls");

        isblackjack = isbj(player, player_count, player_sum);

        if (check(isblackjack))
            break;

        if (player_count == 1)
            show_dealer();

        show_hand(player, player_count);
        std::cout << " (" << player_sum << ")" << std::endl;

        if (player_count == 1)
        {

            if (player[0].value == player[1].value || (player[0].number == ace && player[1].number == ace))
            {
                std::cout << "| Get card(+) | Split(/) | Don't want(-) |" << std::endl;
                avaibleForSplit = true;
            }
            else
            {
                std::cout << "| Get card(+) | Double(*) | Don't want(-) |" << std::endl;
            }
        }
        else
        {
            std::cout << "| Get card(+) | Don't want(-) |" << std::endl;
        }

        std::string answer;
        std::cin >> answer;

        if (answer == "+")
        {
            request_card();
        }
        else if (answer == "-")
        {
            open_dealer_hand();
            break;
        }
        else if (answer == "/" && avaibleForSplit)
        {
            SplitCard(*this);
            break;
        }
        else if (answer == "*" && player_count == 1)
        {
            isdouble = true;
            request_card();
        }
        else
        {
            system("cls");
            std::cout << "Invalid format" << std::endl;
            Sleep(300);
        }
    }

    played++;
}

void Blackjack::show_dealer()
{
    std::cout << "-----DEALER------" << std::endl;
    show_hand(dealer, dealer_count - 1);
    for (int i = 0; i < 4; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < 6; j++)
        {
            if (i == 1 && j == 1)
            {
                std::cout << "B";
            }
            else if (i == 2 && j == 4)
            {
                std::cout << "J";
            }
            else
            {
                std::cout << "۞";
            }
        }
        std::cout << std::endl
                  << std::flush;
    }
    std::cout << "-----------------" << std::endl;
}

void Blackjack::show_hand(Card k[], int size)
{
    for (int i = 0; i <= size; i++)
    {
        std::cout << k[i] << std::endl
                  << std::flush;
        Sleep(500);
    }
}

void Blackjack::deal_cards()
{
    for (int i = 0; i < 2; i++)
    {
        dealer[i] = draw_card();
        player[i] = draw_card();
    }
    for (int i = 0; i < 2; i++)
    {
        player_sum += player[i].value;
        dealer_sum += dealer[i].value;
    }
}

bool Blackjack::check(int isblackjack)
{
    if (isblackjack == 1)
    {
        // blackjack
        show_hand(player, player_count);
        std::cout << "Blackjack" << std::endl;
        Sleep(1000);
        open_dealer_hand();
        return 1;
    }
    else if (isblackjack == -1)
    {
        // busted
        show_hand(player, player_count);
        std::cout << " (" << player_sum << ")" << std::endl;
        std::cout << "You busted" << std::endl;
        Sleep(1000);
        open_dealer_hand();
        return 1;
    }
    else if (isdouble)
    {
        // double
        show_hand(player, player_count);
        std::cout << " (" << player_sum << ")" << std::endl;
        Sleep(1000);
        open_dealer_hand();
        isdouble = false;
        return 1;
    }
    return 0;
}

void Blackjack::request_card()
{
    player[++player_count] = draw_card();
    player_sum += player[player_count].value;
}

void Blackjack::open_dealer_hand()
{
    system("cls");

    int win = (isdouble) ? 2 : 1;

    std::cout << "you          " << player_sum << std::endl;
    std::cout << "-----DEALER------" << std::endl;

    while (1)
    {
        isbj(dealer, dealer_count, dealer_sum);
        if (dealer_sum < 17)
        {
            dealer[++dealer_count] = draw_card();
            dealer_sum += dealer[dealer_count].value;
        }
        else if (dealer_sum <= 21)
        {
            if (player_sum <= 21)
            {
                if (dealer_sum == player_sum)
                {
                    result = "     YOU DID NOT LOST";
                }
                if (dealer_sum > player_sum)
                {
                    result = "\tYOU LOST";
                    won -= win;
                }
                if (dealer_sum < player_sum)
                {
                    result = "\tYOU WON";
                    won += win;
                }
            }
            else
            {
                result = "\tYOU LOST";
                won -= win;
            }
            break;
        }
        else
        {
            if (player_sum > 21)
            {
                result = "     YOU DID NOT LOST";
            }
            else
            {
                result = "\tYOU WON";
                won += win;
            }
            break;
        }
    }
    show_hand(dealer, dealer_count);
    std::cout << "---------------" << std::endl;
    std::cout << "dealer      " << dealer_sum << std::endl;
    if (win > 0)
        std::cout << std::endl
                  << result << " " << win << std::endl;
    else
        std::cout << std::endl
                  << result << std::endl;
}

int Blackjack::isbj(Card k[], int count, int &sum)
{
    for (int i = 0; i <= count && sum < 21; i++)
    {
        if (k[i].value == ace)
        {
            k[i].value += (sum + 10 > 21) ? 0 : 10;
            sum += (sum + 10 > 21) ? 0 : 10;
        }
    }
    if (sum > 21)
    {
        for (int i = 0; i <= count && sum > 21; i++)
        {
            if (k[i].value == 11)
            {
                k[i].value -= 10;
                sum -= 10;
            }
        }
        if (sum < 21)
            return 0;
        if (sum == 21)
            return 1;

        return -1;
    }
    else if (sum < 21)
    {
        return 0;
    }
    else if (sum == 21)
    {
        return 1;
    }
}

SplitCard::SplitCard(Blackjack &b) : Blackjack(0), split_count(1), split_sum(0)
{

    // desteyi kopyalama
    top = b.top;
    for (int i = 0; i < 52; i++)
    {
        cards[i] = b.cards[i];
    }

    // player ve dealer kopyalama
    for (int i = 0; i < 11; i++)
    {
        player[i] = Card(b.player[i]);
        dealer[i] = Card(b.dealer[i]);
    }

    split_double();

    while (true)
    {

        system("cls");
        isblackjack = isbj(player, player_count, player_sum);
        s_isblackjack = isbj(split_card, split_count, split_sum);

        if (check(isblackjack, s_isblackjack))
            break;

        show_hand(player, player_count);
        std::cout << " (" << player_sum << ")";
        std::cout << std::endl
                  << "-----------------" << std::endl;
        show_hand(split_card, split_count);
        std::cout << " (" << split_sum << ")";

        std::cout << "\n1 -> " << player_info << "\n2 -> " << split_info << std::endl
                  << std::endl;

        std::cout << "| 1 | 2 | - |" << std::endl;
        std::cout << std::endl;

        std::string answer;
        std::cin >> answer;

        if (answer == "1")
        {
            request_card(1);
        }
        else if (answer == "2")
        {
            request_card(2);
        }
        else if (answer == "-")
        {
            open_dealer_hand();
            break;
        }
        else
        {
            system("cls");
            std::cout << "Invalid format" << std::endl;
            Sleep(300);
        }
    }

    b.top = top;
    b.won += won;
}

SplitCard::~SplitCard() { delete[] split_card; }

bool SplitCard::check(int isblackjack, int s_isblackjack)
{

    if (isblackjack == 1)
    {
        player_info = "Blackjack";
        if (s_isblackjack == -1)
        {
            show_hand(player, player_count);
            std::cout << "-----------------" << std::endl;
            show_hand(split_card, split_count);
            std::cout << "\n1 -> Blackjack\n2 -> Busted (" << split_sum << ")\n";
            Sleep(2000);
            open_dealer_hand();
            return 1;
        }
        else if (s_isblackjack == 1)
        {
            show_hand(player, player_count);
            std::cout << "-----------------" << std::endl;
            show_hand(split_card, split_count);
            std::cout << "Both are blackjack" << std::endl;
            Sleep(2000);
            open_dealer_hand();
        }
    }
    if (isblackjack == -1)
    {
        player_info = "Busted";
        if (s_isblackjack == -1)
        {
            show_hand(player, player_count);
            std::cout << "-----------------" << std::endl;
            show_hand(split_card, split_count);
            std::cout << player_sum << std::endl
                      << split_sum << std::endl;
            std::cout << "Both are busted" << std::endl;
            Sleep(1000);
            open_dealer_hand();
            return 1;
        }
        else if (s_isblackjack == 1)
        {
            show_hand(player, player_count);
            std::cout << "-----------------" << std::endl;
            show_hand(split_card, split_count);
            std::cout << player_sum << std::endl
                      << split_sum << std::endl;
            Sleep(1000);
            open_dealer_hand();
            return 1;
        }
    }
    if (isblackjack == 0)
    {
        player_info = "Not busted yet";
        if (s_isblackjack == 1)
        {
            split_info = "Blackjack";
        }
        else if (s_isblackjack == -1)
        {
            split_info = "Busted";
        }
        else
        {
            split_info = "Not busted yet";
        }
    }

    return 0;
}

void SplitCard::request_card(int c)
{

    if (c == 1)
    {
        // give card to first hand
        player[++player_count] = draw_card();
        player_sum += player[player_count].value;
    }
    else
    {
        // give card to second hand
        split_card[++split_count] = draw_card();
        split_sum += split_card[split_count].value;
    }
}

void SplitCard::split_double()
{

    split_card = new Card[11];

    split_card[0] = player[1];
    split_card[1] = draw_card();
    split_sum = split_card[0].value + split_card[1].value;

    player[1] = draw_card();
    player_sum = player[0].value + player[1].value;

    dealer_sum = dealer[0].value + dealer[1].value;
}

void SplitCard::open_dealer_hand()
{

    system("cls");

    std::cout << "first          " << player_sum << std::endl;
    std::cout << "second         " << split_sum << std::endl;
    std::cout << "-----DEALER------" << std::endl;

    while (1)
    {
        isbj(dealer, dealer_count, dealer_sum);
        if (dealer_sum < 17)
        {
            // give cards to the dealer till the dealer reach 17
            dealer[++dealer_count] = draw_card();
            dealer_sum += dealer[dealer_count].value;
        }
        else if (dealer_sum <= 21)
        {
            // dealer is not busted
            if (player_sum <= 21)
            {
                if (dealer_sum == player_sum)
                {
                    result = "TIE in first hand";
                }
                if (dealer_sum > player_sum)
                {
                    result = "YOU LOST in first hand";
                    won--;
                }
                if (dealer_sum < player_sum)
                {
                    result = "YOU WON in first hand";
                    won++;
                }
            }
            else if (player_sum > 21)
            {
                result = "YOU LOST in first hand";
                won--;
            }

            if (split_sum <= 21)
            {
                if (dealer_sum == split_sum)
                {
                    second_result = "TIE in second hand";
                }
                if (dealer_sum > split_sum)
                {
                    second_result = "YOU LOST in second hand";
                    won--;
                }
                if (dealer_sum < split_sum)
                {
                    second_result = "YOU WON in second hand";
                    won++;
                }
            }
            else if (split_sum > 21)
            {
                second_result = "YOU LOST in second hand";
                won--;
            }
            break;
        }
        else
        {
            // dealer is busted

            if (player_sum > 21)
            {
                result = "TIE in first hand";
            }
            else if (player_sum <= 21)
            {
                result = "YOU WON in first hand";
                won++;
            }
            if (split_sum > 21)
            {
                second_result = "TIE in second hand";
            }
            else if (split_sum <= 21)
            {
                second_result = "YOU WON in second hand";
                won++;
            }

            break;
        }
    }

    show_hand(dealer, dealer_count);
    std::cout << "---------------" << std::endl;
    std::cout << "dealer         " << dealer_sum << std::endl;
    std::cout << std::endl
              << result << "\n"
              << second_result << std::endl;
}