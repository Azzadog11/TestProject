// AARON BLACKLER S5259028  
// ASSIGNMENT 2
// Q1

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
#include <fstream>

using namespace std;
// Oh Hello there
#define THISISATEST 1000;
bool check_number(char number[])
{
  int i = 0;

  // checking for negative numbers
  if (number[0] == '-')
    i = 1;
  for (; number[i] != 0; i++)
  {
    // if (number[i] > '9' || number[i] < '0')
    if (!isdigit(number[i]))
      return false;
  }
  return true;
}

class Game
{
private:
  vector<string> found_words;
  unordered_map<string, int> all_words;

public:
  vector<vector<char>> gameboard;
  int word_length;
  bool check_all_lengths = false;
  // Constructor
  Game(int arg_num, char *arg_data[])
  {
    if (arg_num == 1 || arg_num > 3)
    {
      cout << "Invalid Input, options are:" << endl;
      cout << "<game size>\n<game size> <word size>\n<filename>\n<filename> <word size>";
      exit(0);
    }
    // LOADING IN DICTIONARY
    string word;
    fstream dict("dictionary.txt");
    // Checks that dictionary.txt exists
    if (!dict.is_open())
    {
      cout << "Unable to open: " << endl;
      exit(0);
    }
    // Iterating through dictionary.txt and storing words into unordered map
    // Words are mapped to int 0, once that word is found in board then it will add 1
    else
    {
      while (dict >> word)
      {
        all_words.insert({word, 1});
      }
    }
    dict.close();

    // IF MORE THAN ONE ARGUMENT
    if (arg_num > 2)
    {
      word_length = stoi(arg_data[2]);
      // IF ARGUMENT IS NUMBER
      if (check_number(arg_data[1]))
      {
        gameboard = random_char_vec(stoi(arg_data[1]));
      }
      else
      {
        // Tells algorithm to check all lengths
        fstream file(arg_data[1]);
        if (!file.is_open())
        {
          cout << "Unable to open: " << arg_data[1] << endl;
          exit(0);
        }
        vector<string> lines;
        vector<char> temp;
        string line;
        // Reads file line-by-line
        while (file >> line)
        {
          lines.push_back(line);
        }
        // Takes a line and iterates through characters
        for (auto line : lines)
        {
          for (auto letter : line)
          {
            temp.push_back(letter); // Appends characters letter by letter
          }
          // Appends char vector to 2d gameboard vector
          gameboard.push_back(temp);
          temp.clear(); // Clears vector ready for next letters
        }
      }
    }
    else if (check_number(arg_data[1]))
    {
      check_all_lengths = true;
      gameboard = random_char_vec(stoi(arg_data[1]));
    }
    else
    {
      // Tells algorithm to check all lengths
      check_all_lengths = true;
      fstream file("puzzle_maths.txt");
      if (!file.is_open())
      {
        cout << "Unable to open: " << endl;
        exit(0);
      }
      vector<string> lines;
      vector<char> temp;
      string line;
      // Reads file line-by-line
      while (file >> line)
      {
        lines.push_back(line);
      }
      // Takes a line and iterates through characters
      for (auto line : lines)
      {
        for (auto letter : line)
        {
          temp.push_back(letter); // Appends characters letter by letter
        }
        // Appends char vector to 2d gameboard vector
        gameboard.push_back(temp);
        temp.clear(); // Clears vector ready for next letters
      }
    }
  }

  // COPY CONSTRUCTOR WITH GAME DATATYPE
  Game(const Game &game, int = 0)
  {
    this->found_words = game.found_words;
    this->all_words = game.all_words;
    this->gameboard = game.gameboard;
    this->word_length = game.word_length;
    this->check_all_lengths = game.check_all_lengths;
  }

  // PROTOTYPES
  // Checks if a string is entirely numbers
  // Used to see if command line input is filename or number.
  bool is_number(const string word) // DONE
  {
    string::const_iterator it = word.begin();
    while (it != word.end() && isdigit(*it))
      it++;
    return !word.empty() && it == word.end();
  }
  // Finds words
  vector<string> found();
  // Creates random vector of chars in a square
  vector<vector<char>> random_char_vec(const int &vec_size);
  // Checks for words in a vector of chars
  vector<string> check_for_word(const int &length, const vector<char> &letters); // DONE
  // Checks a 2d array for words
  vector<string> check_2d_vec(const vector<vector<char>> &game_data, const int &word_length);
  // Returns vector of vectors of chars going right to left, top to bottom
  vector<vector<char>> get_right_left(vector<vector<char>> game_data); // DONE
  // Returns vector of vectors of chars going top to bottom
  vector<vector<char>> get_top_bottom(vector<vector<char>> game_data); // DONE
  // Returns vector of vectors of chars going bottom to top
  vector<vector<char>> get_bottom_top(vector<vector<char>> game_data); // DONE
  // Returns vector of vectors of chars going diagonal upwards
  vector<vector<char>> get_diag_up(vector<vector<char>> game_data, const int &word_size); // DONE
  // Returns vector of vectors of chars going diagonal downwards
  vector<vector<char>> get_diag_down(vector<vector<char>> game_data, const int &word_size); // DONE
  // Returns vector of vectors of chars going diagonal upwards in reverse
  vector<vector<char>> get_diag_up_rev(vector<vector<char>> game_data, const int &word_size); // DONE
  // Returns vector of vectors of chars going diagonal downwards in reverse
  vector<vector<char>> get_diag_down_rev(vector<vector<char>> game_data, const int &word_size); // DONE

  void operator=(const Game &game);                               // Overloads = operator
  friend ostream &operator<<(ostream &os, const Game &game);      // Overloads << operator
  friend bool operator!=(const Game &game1, const Game &game2);   // Overload != operator
  friend string operator==(const Game &game1, const Game &game2); // Overloads == operator
};

int main(int argc, char *argv[])
{
  auto start = clock();
  Game game(argc, argv);
  //cout << game << endl;
  vector<string> words = game.found();
  // Since I have printed them out in the function already I have commented out this 
  // print function. I did this because 90% of the CPU time seems to be printing 
  //for (auto l : words)
  //  cout << l << endl;
  cout << "Found " << words.size() << " words" << endl;

  auto cpu_time = clock() - start;
  cout << "Cpu time = " << double(cpu_time) / CLOCKS_PER_SEC << endl;

  Game game1(game);
  Game game2 = game1;

  if (game1 != game)
    cout << "Error in game copy 1" << endl;
  if (game2 != game)
    cout << "Error in game copy 2" << endl;

  cout << "Games same " << (game2 == game1) << endl;

  return 0;
}

// Checks a vector for words
vector<string> Game::check_for_word(const int &length, const vector<char> &letters)
{
  string temp;
  vector<string> found_words;
  int found_row = 0;
  // Iterates through possible starting points
  for (int i = 0; i <= letters.size() - length; i++)
  {
    // Iterates through chars and makes a string until length is reached
    for (int j = 0; j < length; j++)
    {
      temp.push_back(letters[i + j]);
    }
    // Searches through unordered map for temp
    auto found = all_words.find(temp);
    // If 1 is returned then word gets appended to found_words
    if (found != all_words.end())
    {
      found_words.push_back(temp);
      found_row = i;
    }
    temp.clear();
  }
  return found_words;
}

// Checks a 2d array for words
vector<string> Game::check_2d_vec(const vector<vector<char>> &game_data, const int &word_length)
{
  vector<string> words_found;
  int line_count = 0;
  for (auto line : game_data)
  {
    line_count += 1;
    auto word_vec = check_for_word(word_length, line);
    for (auto word : word_vec)
    {
      //cout << "@ Line: " << line_count << ": " << word << endl;
      words_found.push_back(word);
    }
  }
  return words_found;
}

// Returns vector of vectors of chars going right to left, top to bottom
vector<vector<char>> Game::get_right_left(vector<vector<char>> game_data)
{
  for (int i = 0; i < game_data.size(); i++)
  {
    for (int j = 0; j < game_data[i].size() / 2; j++)
    {
      // Left becomes right and right becomes left
      swap(game_data[i][j], game_data[i][game_data[i].size() - j - 1]);
    }
  }
  return game_data;
}

// Returns vector of vectors of chars going top to bottom
vector<vector<char>> Game::get_top_bottom(vector<vector<char>> game_data)
{
  vector<vector<char>> new_game_data(game_data[0].size());
  for (int i = 0; i < game_data[0].size(); i++)
  {
    for (int j = 0; j < game_data.size(); j++)
    {
      new_game_data[i].push_back(game_data[j][i]);
    }
  }
  return new_game_data;
}

// Returns vector of vectors of chars going bottom to top
vector<vector<char>> Game::get_bottom_top(vector<vector<char>> game_data)
{
  vector<vector<char>> new_game_data(game_data[0].size());
  for (int i = 0; i < game_data[0].size(); i++)
  {
    for (int j = 0; j < game_data.size(); j++)
    {
      new_game_data[i].push_back(game_data[game_data.size() - j - 1][i]);
    }
  }
  return new_game_data;
}

// Returns vector of vectors of chars going diagonal upwards
vector<vector<char>> Game::get_diag_up(vector<vector<char>> game_data, const int &word_size)
{
  vector<vector<char>> new_game_data;
  vector<char> temp;
  for (int i = 0; i < game_data.size(); i++)
  {
    for (int j = 0; j < game_data[0].size() && j < i + 1; j++)
    {
      temp.push_back(game_data[i - j][j]);
    }
    if (temp.size() >= word_size)
    {
      new_game_data.push_back(temp);
    }
    temp.clear();
    // For last iteration of i starts another loop to get last line
    if (i == game_data.size() - 1)
    {
      for (int k = 0; k < game_data[0].size(); k++)
      {
        for (int l = 0; l < game_data[0].size() - 1 && l < game_data[0].size() - k - 1; l++)
        {
          temp.push_back(game_data[game_data.size() - 1 - l][k + l + 1]);
        }
        if (temp.size() >= word_size)
        {
          new_game_data.push_back(temp);
        }
        temp.clear();
      }
    }
  }
  return new_game_data;
}

// Returns vector of vectors of chars going diagonal downwards
vector<vector<char>> Game::get_diag_down(vector<vector<char>> game_data, const int &word_size)
{
  vector<vector<char>> new_game_data;
  vector<char> temp;
  for (int i = 0; i < game_data.size(); i++)
  {
    for (int j = 0; j < game_data[0].size() && j < i + 1; j++)
    {
      temp.push_back(game_data[game_data.size() - i + j - 1][j]);
    }
    if (temp.size() >= word_size)
    {
      new_game_data.push_back(temp);
    }
    temp.clear();
    // For last iteration of i starts another loop to get last line
    if (i == game_data.size() - 1)
    {
      for (int k = 0; k < game_data[0].size(); k++)
      {
        for (int l = 0; l < game_data[0].size() - 1 && l < game_data[0].size() - k - 1; l++)
        {
          temp.push_back(game_data[l][k + l + 1]);
        }
        if (temp.size() >= word_size)
        {
          new_game_data.push_back(temp);
        }
        temp.clear();
      }
    }
  }
  return new_game_data;
}

// Returns vector of vectors of chars going diagonal upwards in reverse
vector<vector<char>> Game::get_diag_up_rev(vector<vector<char>> game_data, const int &word_size)
{
  vector<vector<char>> temp_data;
  temp_data = get_right_left(game_data);
  return get_diag_up(temp_data, word_size);
}

// Returns vector of vectors of chars going diagonal downwards in reverse
vector<vector<char>> Game::get_diag_down_rev(vector<vector<char>> game_data, const int &word_size)
{
  vector<vector<char>> temp_data;
  temp_data = get_right_left(game_data);
  return get_diag_down(temp_data, word_size);
}

// Finds words
vector<string> Game::found()
{
  vector<string> words;
  vector<string> temp_words;
  if (!check_all_lengths)
  {
    cout << "Horizontal: " << endl;
    temp_words = check_2d_vec(gameboard, word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking right to left
    cout << "Horizontal r - l: " << endl;
    temp_words = check_2d_vec(get_right_left(gameboard), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking top to bottom
    cout << "Top to bottom: \n(columns and rows are flipped so line = column number)" << endl;
    temp_words = check_2d_vec(get_top_bottom(gameboard), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking bottom to top
    cout << "Bottom to top: \n(columns and rows are flipped so line = column number)" << endl;
    temp_words = check_2d_vec(get_bottom_top(gameboard), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking diagonal l-r up
    cout << "Please do not refer to rest of coordinates as diagonal coordinate is not working:" << endl;
    temp_words = check_2d_vec(get_diag_up(gameboard, word_length), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking diagonal r-l up
    temp_words = check_2d_vec(get_diag_up_rev(gameboard, word_length), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking diagonal l-r down
    temp_words = check_2d_vec(get_diag_down(gameboard, word_length), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    // Checking diagonal r-l down
    temp_words = check_2d_vec(get_diag_down_rev(gameboard, word_length), word_length);
    for (auto i : temp_words)
    {
      words.push_back(i);
    }
    temp_words.clear();

    sort(begin(words), end(words));
    return words;
  }

  else
  {
    for (int word_length = 2; word_length < 14 && word_length < gameboard[0].size(); word_length++)
    {
      cout << "CURRENT WORD LENGTH: " << word_length << endl;
      cout << "Horizontal: " << endl;
      temp_words = check_2d_vec(gameboard, word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking right to left
      cout << "Horizontal r - l: " << endl;
      temp_words = check_2d_vec(get_right_left(gameboard), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking top to bottom
      cout << "Top to bottom: (columns and rows are flipped so line = column number)" << endl;
      temp_words = check_2d_vec(get_top_bottom(gameboard), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking bottom to top
      cout << "Bottom to top: (columns and rows are flipped so line = column number)" << endl;
      temp_words = check_2d_vec(get_bottom_top(gameboard), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking diagonal l-r up
      cout << "Diagonal: (Position not working)" << endl;
      temp_words = check_2d_vec(get_diag_up(gameboard, word_length), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking diagonal r-l up
      temp_words = check_2d_vec(get_diag_up_rev(gameboard, word_length), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking diagonal l-r down
      temp_words = check_2d_vec(get_diag_down(gameboard, word_length), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      // Checking diagonal r-l down
      temp_words = check_2d_vec(get_diag_down_rev(gameboard, word_length), word_length);
      for (auto i : temp_words)
      {
        words.push_back(i);
      }
      temp_words.clear();

      sort(begin(words), end(words));
    }
    return words;
  }
  return words;
}

// Creates random vector of chars in a square
vector<vector<char>> Game::random_char_vec(const int &vec_size)
{
  vector<vector<char>> result;
  vector<char> temp;
  srand(time(NULL));
  for (int i = 0; i < vec_size; i++)
  {
    for (int j = 0; j < vec_size; j++)
    {
      char c = 'a' + rand() % 26;
      temp.push_back(c);
    }
    result.push_back(temp);
    temp.clear();
  }
  return result;
}

// Overloads = operator
void Game::operator=(const Game &game)
{
  this->found_words = game.found_words;
  this->all_words = game.all_words;
  this->gameboard = game.gameboard;
  this->word_length = game.word_length;
  this->check_all_lengths = game.check_all_lengths;
}
// Overloads << operator
ostream &operator<<(ostream &os, const Game &game)
{
  int row_count = 0;
  for (auto i : game.gameboard)
  {
    row_count += 1;
    os << row_count << " "; 
    for (auto j : i)
    {
      os << j;
    }
    os << "\n";
  }
  return os;
}

// Overload != operator
bool operator!=(const Game &game1, const Game &game2)
{
  return !(game1.gameboard == game2.gameboard && game1.all_words == game2.all_words);
}

// Overloads == operator
string operator==(const Game &game1, const Game &game2)
{
  if (game1.gameboard == game2.gameboard)
  {
    return "True";
  }
  else
  {
    return "False";
  }
}
