// Tic_Tac_Toe.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <chrono>
#include <thread>

char gameMap[9];

enum Role : char
{
    Player = 'o',
    AI = 'x',
    Empty = ' '
};

bool setRole(int x, int y, Role role) {
    if (x < 1 || x > 3) return false;
    if (y < 1 || y > 3) return false;
    gameMap[((x - 1) * 3) + y - 1] = role;
    return true;
}

Role getRole(int x, int y) {
    if (x < 1 || x > 3) return Role::Empty;
    if (y < 1 || y > 3) return Role::Empty;
    return (Role)gameMap[((x - 1) * 3) + y - 1];
}

/**
 * @brief 重置地图
*/
void resetMap() {
    memset(gameMap, Role::Empty, sizeof(gameMap));
}


/**
 * @brief 打印井字棋的UI
*/
void PrintUI() {
//std::cout << "     |     |     " << std::endl;
//std::cout << "     |     |     " << std::endl;
//std::cout << "-----------------" << std::endl;
//std::cout << "     |     |     " << std::endl;
//std::cout << "     |     |     " << std::endl;
//std::cout << "-----------------" << std::endl;
//std::cout << "     |     |     " << std::endl;
//std::cout << "     |     |     " << std::endl;

//std::cout << "  \\/ |  -  |     " << std::endl;
//std::cout << "  /\\ |  -  |     " << std::endl;

    for (size_t i = 1; i <= 3; i++)
    {
        if (i - 1) {
            std::cout << "-----------------" << std::endl;
        }
        for (size_t j = 1; j <= 3; j++)
        {
            if (j - 1) {
                std::cout << "|";
            }
            switch (getRole(static_cast<int>(i), static_cast<int>(j))) // 第几行就是上一行*3， 然后加上第几个
            {
            case Role::Player:
                std::cout << "  \\/ ";
                break;
            case Role::AI:
                std::cout << "  -  ";
                break;
            case Role::Empty:
                std::cout << "     ";
            default:
                break;
            }
        }
        std::cout << std::endl;
        for (size_t j = 1; j <= 3; j++)
        {
            if (j - 1) {
                std::cout << "|";
            }
            switch (getRole(static_cast<int>(i), static_cast<int>(j)))
            {
            case Role::Player:
                std::cout << "  /\\ ";
                break;
            case Role::AI:
                std::cout << "  -  ";
                break;
            case Role::Empty:
                std::cout << "     ";
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * @brief 放置后检查是否赢了游戏
 * @return 是那个角色赢得游戏, Role::Empty 表示没有角色赢游戏
*/
Role CheckWom(int x/*行*/, int y/*列*/)
{
    Role currentRole = getRole(x, y);
    if (currentRole == Role::Empty) return Role::Empty; // 如果出了意外 并没有放置...

    int solt = ((x - 1) * 3) + y;
    switch (solt)
    {
    case 1:
        // 横
        if (getRole(x, y + 1) == currentRole && getRole(x, y + 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x + 1, y) == currentRole && getRole(x + 2, y) == currentRole) return currentRole;
        // 斜
        if (getRole(x + 1, y + 1) == currentRole && getRole(x + 2, y + 2) == currentRole) return currentRole;
        break;
    case 2:
        // 横
        if (getRole(x, y - 1) == currentRole && getRole(x, y + 1) == currentRole) return currentRole;
        // 竖
        if (getRole(x + 1, y) == currentRole && getRole(x + 2, y) == currentRole) return currentRole;
        // 斜
        //if (getRole(x + 1, y + 1) == currentRole && getRole(x + 2, y + 2) == currentRole) return currentRole;
        break;
    case 3:
        // 横
        if (getRole(x, y - 1) == currentRole && getRole(x, y - 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x + 1, y) == currentRole && getRole(x + 2, y) == currentRole) return currentRole;
        // 斜
        if (getRole(x + 1, y - 1) == currentRole && getRole(x + 2, y - 2) == currentRole) return currentRole;
        break;
    case 4:
        // 横
        if (getRole(x, y + 1) == currentRole && getRole(x, y + 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x - 1, y) == currentRole && getRole(x + 1, y) == currentRole) return currentRole;
        // 斜
        break;
    case 5:
        // 横
        if (getRole(x, y + 1) == currentRole && getRole(x, y - 1) == currentRole) return currentRole;
        // 竖
        if (getRole(x + 1, y) == currentRole && getRole(x - 1, y) == currentRole) return currentRole;
        // 斜
        if (getRole(x - 1, y - 1) == currentRole && getRole(x + 1, y + 1) == currentRole) return currentRole;
        // 斜2
        if (getRole(x + 1, y - 1) == currentRole && getRole(x - 1, y + 1) == currentRole) return currentRole;
        break;
    case 6:
        // 横
        if (getRole(x, y - 1) == currentRole && getRole(x, y - 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x + 1, y) == currentRole && getRole(x - 1, y) == currentRole) return currentRole;
        // 斜
        break;
    case 7:
        // 横
        if (getRole(x, y + 1) == currentRole && getRole(x, y + 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x - 1, y) == currentRole && getRole(x - 2, y) == currentRole) return currentRole;
        // 斜
        if (getRole(x - 1, y + 1) == currentRole && getRole(x - 2, y + 2) == currentRole) return currentRole;
        break;
    case 8:
        // 横
        if (getRole(x, y + 1) == currentRole && getRole(x, y - 1) == currentRole) return currentRole;
        // 竖
        if (getRole(x - 1, y) == currentRole && getRole(x - 2, y) == currentRole) return currentRole;
        // 斜
        break;
    case 9:
        // 横
        if (getRole(x, y - 1) == currentRole && getRole(x, y - 2) == currentRole) return currentRole;
        // 竖
        if (getRole(x - 1, y) == currentRole && getRole(x - 2, y) == currentRole) return currentRole;
        // 斜
        if (getRole(x - 1, y - 1) == currentRole && getRole(x - 2, y - 2) == currentRole) return currentRole;
        break;
    default:
        break;
    }
    return Role::Empty;
}

/**
 * @brief 表示一个点如果设置此角色会不会赢得游戏
 * @return 
*/
Role ifWom(int x, int y, Role role)
{
    if (getRole(x, y) != Role::Empty) return Role::Empty;

    int solt = ((x - 1) * 3) + y;
    switch (solt)
    {
    case 1:
        // 横
        if (getRole(x, y + 1) == role && getRole(x, y + 2) == role) return role;
        // 竖
        if (getRole(x + 1, y) == role && getRole(x + 2, y) == role) return role;
        // 斜
        if (getRole(x + 1, y + 1) == role && getRole(x + 2, y + 2) == role) return role;
        break;
    case 2:
        // 横
        if (getRole(x, y - 1) == role && getRole(x, y + 1) == role) return role;
        // 竖
        if (getRole(x + 1, y) == role && getRole(x + 2, y) == role) return role;
        // 斜
        //if (getRole(x + 1, y + 1) == role && getRole(x + 2, y + 2) == role) return role;
        break;
    case 3:
        // 横
        if (getRole(x, y - 1) == role && getRole(x, y - 2) == role) return role;
        // 竖
        if (getRole(x + 1, y) == role && getRole(x + 2, y) == role) return role;
        // 斜
        if (getRole(x + 1, y - 1) == role && getRole(x + 2, y - 2) == role) return role;
        break;
    case 4:
        // 横
        if (getRole(x, y + 1) == role && getRole(x, y + 2) == role) return role;
        // 竖
        if (getRole(x - 1, y) == role && getRole(x + 1, y) == role) return role;
        // 斜
        break;
    case 5:
        // 横
        if (getRole(x, y + 1) == role && getRole(x, y - 1) == role) return role;
        // 竖
        if (getRole(x + 1, y) == role && getRole(x - 1, y) == role) return role;
        // 斜
        if (getRole(x - 1, y - 1) == role && getRole(x + 1, y + 1) == role) return role;
        // 斜2
        if (getRole(x + 1, y - 1) == role && getRole(x - 1, y + 1) == role) return role;
        break;
    case 6:
        // 横
        if (getRole(x, y - 1) == role && getRole(x, y - 2) == role) return role;
        // 竖
        if (getRole(x + 1, y) == role && getRole(x - 1, y) == role) return role;
        // 斜
        break;
    case 7:
        // 横
        if (getRole(x, y + 1) == role && getRole(x, y + 2) == role) return role;
        // 竖
        if (getRole(x - 1, y) == role && getRole(x - 2, y) == role) return role;
        // 斜
        if (getRole(x - 1, y + 1) == role && getRole(x - 2, y + 2) == role) return role;
        break;
    case 8:
        // 横
        if (getRole(x, y + 1) == role && getRole(x, y - 1) == role) return role;
        // 竖
        if (getRole(x - 1, y) == role && getRole(x - 2, y) == role) return role;
        // 斜
        break;
    case 9:
        // 横
        if (getRole(x, y - 1) == role && getRole(x, y - 2) == role) return role;
        // 竖
        if (getRole(x - 1, y) == role && getRole(x - 2, y) == role) return role;
        // 斜
        if (getRole(x - 1, y - 1) == role && getRole(x - 2, y - 2) == role) return role;
        break;
    default:
        break;
    }
    return Role::Empty;
}

/**
 * @brief 是否有空槽
 * @return 
*/
bool hasEmptySolt()
{
    for (auto c : gameMap)
    {
        if (c == Role::Empty) return true;
    }
    return false;
}

void soltToxy(int solt, int* x, int* y) {
    *x = solt / 3;
    *y = solt % 3;
    if (*y)
        (*x)++;
    else
        *y = 3;
}

void AIStep(int* x, int* y) {
    // 首先看下在那个空格会赢
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            if (ifWom(i, j, Role::AI) == Role::AI) {
                *x = i;
                *y = j;
                return;
            }
        }
    }

    // 然后看玩家下在哪个空格会赢
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            if (ifWom(i, j, Role::Player) == Role::Player) {
                *x = i;
                *y = j;
                return;
            }
        }
    }

    // 检查下在中心点
    if (getRole(2, 2) == Role::Empty) {
        *x = 2;
        *y = 2;
        return;
    }

    // 检查四个角落
    if (getRole(1, 1) == Role::Empty) {
        *x = 1;
        *y = 1;
        return;
    }
    if (getRole(1, 3) == Role::Empty) {
        *x = 1;
        *y = 3;
        return;
    }
    if (getRole(3, 1) == Role::Empty) {
        *x = 3;
        *y = 1;
        return;
    }
    if (getRole(3, 3) == Role::Empty) {
        *x = 3;
        *y = 3;
        return;
    }

    // 在边缘找
    if (getRole(1, 2) == Role::Empty) {
        *x = 1;
        *y = 2;
        return;
    }
    if (getRole(2, 1) == Role::Empty) {
        *x = 2;
        *y = 1;
        return;
    }
    if (getRole(3, 2) == Role::Empty) {
        *x = 3;
        *y = 2;
        return;
    }
    if (getRole(2, 3) == Role::Empty) {
        *x = 2;
        *y = 3;
        return;
    }
}

int main()
{
    resetMap();

    while (true)
    {
        system("cls");
        PrintUI();
        //std::this_thread::sleep_for(std::chrono::seconds(2));

        // 玩家先手
        std::cout << "输入 1~9：";

        int input;
        std::cin >> input;
        if (input < 1 || input > 9)
        {
            std::cout << "输入不合法 ， 退出。" << std::endl;
            (void)getchar();
            return 0;
        }

        // 解析为xy
        int x, y;

        soltToxy(input, &x, &y);

        
        if (getRole(x, y) != Role::Empty)
        {
            // 重新输入
            continue;
        }
        else {
            setRole(x, y, Role::Player);

            if (CheckWom(x, y) == Role::Player)
            {
                system("cls");
                PrintUI();

                std::cout << "你赢了，好了，要不你关了吧" << std::endl;
                system("pause");
                resetMap();
                continue;
            }

            if (!hasEmptySolt())
            {
                system("cls");
                PrintUI();

                std::cout << "平局..." << std::endl;
                system("pause");
                resetMap();
                continue;
            }

            // AI 下
            AIStep(&x, &y);
            
            // 落棋
            setRole(x, y, Role::AI);

            // 检查AI是否胜利
            if (CheckWom(x, y) == Role::AI)
            {
                system("cls");
                PrintUI();

                std::cout << "你输了， 你还玩什么玩，关了吧" << std::endl;
                system("pause");
                resetMap();
                continue;
            }

            if (!hasEmptySolt())
            {
                system("cls");
                PrintUI();

                std::cout << "平局..." << std::endl;
                system("pause");
                resetMap();
                continue;
            }
        }

    }

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
