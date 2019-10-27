#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "main.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "pickup.hpp"
#include "collisionPlatform.hpp"
#include "textureHolder.hpp"
#include "timeExtension.hpp"
#include "timeRemover.hpp"
#include "goal.hpp"
#include <sstream>
#include <fstream>

#include <iostream>

#include "ResourcePath.hpp"

#include "imgui.h"
#include "imgui-SFML.h"





using namespace sf;
using namespace std;

 vector<vector<char>> levelLayoutVectorStored;


//Prototype for IMGUI load function

void loadLevelForEdit(std::vector<char> &, int &, int &, int &);

//Prototype for load function

void loadLevel(vector<char>&, vector<CollisionPlatform>&, vector<TimeExtension>&,vector<TimeRemover>&, int&, int&, Player&, Goal&, int&);

int main()
{
    TextureHolder holder;
    //Number used to select level upon loading.
    int levelNo = 1;
    //Default player coordinates
    float playerSpawnX = 0;
    float playerSpawnY = 0;
    //Default goal coordinates
    float goalSpawnX = 0;
    float goalSpawnY = 0;
    //Default timer
    float timer = 30.0f;
    //Time left used as a score at the end
    float timeLeft = 0.0f;

    //Vectors for reading in data from text file to generate levels in loadLevel function.
    std::vector<CollisionPlatform> platforms;
    std::vector<TimeExtension> timeExtensions;
    std::vector<TimeRemover> timeRemovers;
    std::vector<char> levelLayout;
    //Row and Column numbers to generate a level using a 2D Array.
    int levelRows = 1;
    int levelColumns = 0;
    
    
    //Size of tiles
    int tileSize = 0;

    //Display related objects
    Vector2f resolution;

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    VideoMode vm(resolution.x, resolution.y);


    //TEXT-RELATED TYPES AND OBJECTS


    Font font;
    font.loadFromFile(resourcePath() + "fonts/VT323-Regular.ttf");
    //font.loadFromFile(resourcePath() + "zombiecontrol.ttf");
    
    
    Text timeRemaining;
    timeRemaining.setFont(font);
    timeRemaining.setCharacterSize(55);
    timeRemaining.setFillColor(Color::White);
    timeRemaining.setString("TIME: ");



    Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(110);
    titleText.setFillColor(Color::Yellow);
    titleText.setString("Time To Kill");

    FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.left+titleRect.width/2.0f, titleRect.top+titleRect.height/2.0f);
    titleText.setPosition(resolution.x/2, resolution.y/4);


    Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(55);
    menuText.setFillColor(Color::White);
    menuText.setString("PRESS ENTER TO START");

    FloatRect menuRect = menuText.getLocalBounds();
    menuText.setOrigin(menuRect.left+menuRect.width/2.0f, menuRect.top+menuRect.height/2.0f);
    menuText.setPosition(resolution.x/2, resolution.y/2);

    Text editorText;
    editorText.setFont(font);
    editorText.setCharacterSize(35);
    editorText.setFillColor(Color::Magenta);
    editorText.setString("(Press LCTRL to edit levels)");
    
    FloatRect editorRect = editorText.getLocalBounds();
    editorText.setOrigin(editorRect.left+editorRect.width/2.0f, editorRect.top+editorRect.height/2.0f);
    editorText.setPosition(resolution.x/2, resolution.y/1.5);
    
    
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(55);
    gameOverText.setFillColor(Color::White);
    gameOverText.setString("Game Over. Press Enter to restart. Best Time Remaining = ");

    FloatRect gameOverRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverRect.left+gameOverRect.width/2.0f, gameOverRect.top+gameOverRect.height/2.0f);
    gameOverText.setPosition(resolution.x/2, resolution.y/2);
    



            //Instantiates Player and Goal. Will be changed with level load, later.

            Player player(playerSpawnX,playerSpawnY);
            Goal goal(goalSpawnX,goalSpawnY);

     // The four states the game will be in, the game starting off in the Menu state.
    enum class State { PAUSED, MENU, GAME_OVER, PLAYING };
    State state = State::MENU;





    // View for game
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    // Renderwindow for game
    RenderWindow window(vm, "Time To Kill, Created by Andrew Bates", Style::Default);

    // Clock
    Clock clock;

    //Imgui bool for loading rows of levels
    bool loadedLevel = false;
    
    //Vector of strings for Imgui Input Fields
    vector<char*> inputStrV;
    

    //Character arrays for Imgui input fields
    
    static char str0[128] = "";
    static char str1[128] = "";
    static char str2[128] = "";
    static char str3[128] = "";
    static char str4[128] = "";
    static char str5[128] = "";
    static char str6[128] = "";
    static char str7[128] = "";
    static char str8[128] = "";
    static char str9[128] = "";
    static char str10[128] = "";
    static char str11[128] = "";
    static char str12[128] = "";
    static char str13[128] = "";
    static char str14[128] = "";
    static char str15[128] = "";
    
    
    
    inputStrV.push_back(str0);
    inputStrV.push_back(str1);
    inputStrV.push_back(str2);
    inputStrV.push_back(str3);
    inputStrV.push_back(str4);
    inputStrV.push_back(str5);
    inputStrV.push_back(str6);
    inputStrV.push_back(str7);
    inputStrV.push_back(str8);
    inputStrV.push_back(str9);
    inputStrV.push_back(str10);
    inputStrV.push_back(str11);
    inputStrV.push_back(str12);
    inputStrV.push_back(str13);
    inputStrV.push_back(str14);
    inputStrV.push_back(str15);
    
    ImGui::SFML::Init(window);

    //Boolean determining whether Imgui menu is open
    bool editingLevel = false;
    
    // Create the background
    VertexArray background;
    // Loading texture sheet
    Texture textureBackground = TextureHolder::GetTexture(resourcePath() + "graphics/background_sheet.png");
    
    // The boundaries of the background
    IntRect backgroundBoundaries;
    
    
    

    while (window.isOpen())
    {
  
       
        // Deltatime updating
        Time dt = clock.restart();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            
            
            
            
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING)
                {
                    state = State::PAUSED;
                }

                // Restart while paused
                else if (event.key.code == Keyboard::Return &&
                         state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                }

                //When the player presses enter on either the Menu or Game Over screen, this will reset
                //the timeleft for their score, levelNo, timer, call the load function, set the state to Playing and restarting the clock.

                else if (event.key.code == Keyboard::Return &&
                         state == State::MENU || event.key.code == Keyboard::Return &&
                         state == State::GAME_OVER )
                {
                    
                    
                    
                    
                    timeLeft = 0;
                    levelNo = 1;
                    timer = 30.0f;
                   
                    //Creating randomly generated background for new level
                    loadLevel(levelLayout,platforms,timeExtensions,timeRemovers,levelRows,levelColumns, player, goal, levelNo);
                    
                    
                    backgroundBoundaries.width = (levelColumns-1) * 62;
                    backgroundBoundaries.height = levelRows * 62;
                    backgroundBoundaries.left = 0;
                    backgroundBoundaries.top = 0;
                    
                    tileSize = createBackground(background, backgroundBoundaries);
                    
                    state = State::PLAYING;
                    clock.restart();
                    
                    
                    
                }

            }
        }


        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }




        // Handle controls while playing
        if (state == State::PLAYING)
        {
            
            
            
            if (levelNo == 4 || timer <= 0.0f)
            {
                std::stringstream ssGameOver;
                timeLeft = timer;
                if(timeLeft < 0)
                    {
                        timeLeft = 0;
                    }
                ssGameOver << "Game Over. Press Enter to restart. Time Remaining = " << timeLeft;
                gameOverText.setString(ssGameOver.str());
                gameOverText.setOrigin(gameOverRect.left+gameOverRect.width/2.0f, gameOverRect.top+gameOverRect.height/2.0f);

                                state = State::GAME_OVER;
            }


            

            // Timer updating
            timer -= dt.asSeconds();
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();


            //Determining which direction the player is able to move based on collision.

           if(player.determineDown(platforms) == false)
                    {
                        player.setCanMoveDown();
                    }
                    else
                        {
                            player.stopCanMoveDown();
                        }

            if(player.determineRight(platforms) == false)
                    {
                        player.setCanMoveLeft();
                    }
                    else
                        {
                            player.stopCanMoveLeft();
                        }
            if(player.determineLeft(platforms) == false)
                    {
                        player.setCanMoveRight();
                    }
                    else
                        {
                            player.stopCanMoveRight();
                        }

            if(player.determineUp(platforms) == false)
                    {
                        player.setCanMoveUp();
                    }
                    else
                        {
                            player.stopCanMoveUp();
                        }


            //Updating the player
            player.update(dtAsSeconds);


            //Testing player collision with all time extension items.
            for (int i = 0; i < timeExtensions.size(); i++)
            {
                if (player.getPosition().intersects
                    (timeExtensions[i].getPosition()))
                    {
                        timeExtensions.erase(timeExtensions.begin() + i);
                        timer += 30;
                    }
            }

            for (int i = 0; i < timeRemovers.size(); i++)
            {
                if (player.getPosition().intersects
                    (timeRemovers[i].getPosition()))
                    {
                        timeRemovers.erase(timeRemovers.begin() + i);
                        timer -= 15;
                    }
            }

            //Testing player collision with the goal.
            if (player.getPosition().intersects
                    (goal.getPosition()))
                    {
                        levelNo++;
                        if(levelNo < 4){
                        loadLevel(levelLayout,platforms,timeExtensions,timeRemovers,levelRows,levelColumns, player, goal, levelNo);
                            
                           
                            
                            //Creating randomly generated background for new level
                            backgroundBoundaries.width = (levelColumns-1) * 62;
                                backgroundBoundaries.height = levelRows * 62;
                                backgroundBoundaries.left = 0;
                                backgroundBoundaries.top = 0;
                                
                                tileSize = createBackground(background, backgroundBoundaries);
                            
                        }
                        
                        
                    }

            //Testing input and permitting the actions of said input based on the movement booleans, eg: player.getCanMoveDirection
            if (Keyboard::isKeyPressed(Keyboard::Left) && player.getCanMoveLeft())
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::Right) && player.getCanMoveRight())
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

            if (Keyboard::isKeyPressed(Keyboard::Z) && player.getCanMoveUp()) {
                        player.jump();
                    }
                    else
                        {
                            player.stopJump();
                        }

            //Allowing the player to dash at an increased speed.
            if (Keyboard::isKeyPressed(Keyboard::X)) {
                        player.dash();
                
                    }
                    else
                        {
                            player.stopDash();
                        }
            
            
            

                        //Update timer visible on HUD.
                        std::stringstream ssTimeRemaining;
                ssTimeRemaining << "TIME: " << timer;
                timeRemaining.setString(ssTimeRemaining.str());

        }

        // Clear all previous drawings on the last frame.
        window.clear();

        
        //Update Imgui
        ImGui::SFML::Update(window, dt);
        


    //Draw everything in PLAYING state
    if (state == State::PLAYING){
        
        // Draw the background
        window.draw(background, &textureBackground);
       
        
        
        mainView.setCenter(player.getCenter());
        window.setView(mainView);

        for(int i = 0; i < platforms.size(); i++){
        window.draw(platforms[i].getSprite());
    }

     for(int i = 0; i < timeExtensions.size(); i++){
        window.draw(timeExtensions[i].getSprite());
    }

    for(int i = 0; i < timeRemovers.size(); i++){
        window.draw(timeRemovers[i].getSprite());
    }

        ImGui::SFML::Render(window);
        
        
        
        window.draw(player.getSprite());
        window.draw(goal.getSprite());
        timeRemaining.setPosition(player.getCenter().x - resolution.x/2, player.getCenter().y - resolution.y/2);
        gameOverText.setPosition(player.getCenter().x, player.getCenter().y);
        window.draw(timeRemaining);

    }
    else
        //Draw everything in MENU state
    if(state == State::MENU)
        {
            
 
            
            if (Keyboard::isKeyPressed(Keyboard::LControl)) {
                
                if(editingLevel == false)
                {
                    editingLevel = true;
                }else
                {
                    editingLevel = false;
                }
                
            }
            
            
            //Show Imgui if boolean permits it
            
            if(editingLevel == true)
            {
                
            ImGui::Begin("LEVEL EDITOR");
            if(ImGui::Button("Load Level to Edit"))
            {
                
                //Clearing previously loaded level if any
                for(int i = 0; i < inputStrV.size();i++)
                {
                    for(int j = 0; j < 128;j++){
                        char p = '\0';
                        inputStrV[i][j] = p;
                        
                        
                    }
                }
                
                std::cout <<"--------------"<< std::endl;
                std::cout <<"Loading Level"<< std::endl;
                loadLevelForEdit(levelLayout,levelRows,levelColumns,levelNo);
                std::cout <<"--------------"<< std::endl;
                std::cout <<"Level Loaded"<< std::endl;
                std::cout <<"--------------"<< std::endl;
                
                
                for(int i = 0; i < levelLayoutVectorStored.size();i++)
                {
                    for(int j = 0; j < levelLayoutVectorStored[i].size();j++){
                        std::cout<< levelLayoutVectorStored[i][j];
                        
                        char p = levelLayoutVectorStored[i][j];
                        
                        inputStrV[i][j] = p;
                        
                        
                    }
                }
                
            }
            
                ImGui::SameLine();
                
            if(ImGui::Button("Save Level"))
            {
                std::cout << "WRITING TO FILE" << std::endl;
                
                ofstream outfile;// declaration of file pointer named outfile
                if(levelNo == 1){
                    
                    outfile.open(resourcePath() + "levels/level1.txt", ios::out); // opens file named "filename" for output
                }
                else if (levelNo == 2)
                {
                    outfile.open(resourcePath() + "levels/level2.txt", ios::out);
                }
                else if (levelNo == 3)
                {
                    outfile.open(resourcePath() + "levels/level3.txt", ios::out);
                }
                
                outfile << str0;
                outfile << str1;
                outfile << str2;
                outfile << str3;
                outfile << str4;
                outfile << str5;
                outfile << str6;
                outfile << str7;
                outfile << str8;
                outfile << str9;
                outfile << str10;
                outfile << str11;
                outfile << str12;
                outfile << str13;
                outfile << str14;
                outfile << str15;
                outfile.close();
                
            }
            
                //Imgui hint with tooltip

                ImGui::Text("Use the fields below to edit the selected level(?)");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("1 = Platform, 2 = Player, 3 = Goal, 4 = Time Extension, 5 = Time Remover, 0 = Blank Space. \n(Note: Each line must be appended with an 'e' until the last line which must be appended with an 'f'. \nThis is for the purpose of loading. \n \n \n Example: \n1111111111e\n1020000001e\n1500400301e\n1111111111f");
                
                
            // Arrow buttons to determine level edited
            
            float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
            ImGui::PushButtonRepeat(true);
            if (ImGui::ArrowButton("##left", ImGuiDir_Left) && levelNo > 1) { levelNo--; }
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::ArrowButton("##right", ImGuiDir_Right) && levelNo < 3) { levelNo++; }
            ImGui::PopButtonRepeat();
            ImGui::SameLine();
            ImGui::Text("%d", levelNo);
            
            //Imgui text fields
            
            ImGui::InputText("Line 0", str0, IM_ARRAYSIZE(str0));
            ImGui::InputText("Line 1", str1, IM_ARRAYSIZE(str1));
            ImGui::InputText("Line 2", str2, IM_ARRAYSIZE(str2));
            ImGui::InputText("Line 3", str3, IM_ARRAYSIZE(str3));
            ImGui::InputText("Line 4", str4, IM_ARRAYSIZE(str4));
            ImGui::InputText("Line 5", str5, IM_ARRAYSIZE(str5));
            ImGui::InputText("Line 6", str6, IM_ARRAYSIZE(str6));
            ImGui::InputText("Line 7", str7, IM_ARRAYSIZE(str7));
            ImGui::InputText("Line 8", str8, IM_ARRAYSIZE(str8));
            ImGui::InputText("Line 9", str9, IM_ARRAYSIZE(str9));
            ImGui::InputText("Line 10", str10, IM_ARRAYSIZE(str10));
            ImGui::InputText("Line 11", str11, IM_ARRAYSIZE(str11));
            ImGui::InputText("Line 12", str12, IM_ARRAYSIZE(str12));
            ImGui::InputText("Line 13", str13, IM_ARRAYSIZE(str13));
            ImGui::InputText("Line 14", str14, IM_ARRAYSIZE(str14));
            ImGui::InputText("Line 15", str15, IM_ARRAYSIZE(str15));
            ImGui::End();
     
            }
            
            window.draw(menuText);
            window.draw(editorText);
            window.draw(titleText);
            
            
            
            
        }
        else
        //Draw everything in GAME_OVER state
        if(state == State::GAME_OVER)
        {
            window.draw(gameOverText);
        }
        
        //Render Imgui
        
        ImGui::SFML::Render(window);
        
        //Displays everything to window.
        window.display();
        
    }
    
    
    
    ImGui::SFML::Shutdown();
    
    return 0;
}

//Function for loading a level into IMGUI
void loadLevelForEdit(std::vector<char> &levelLayout, int &levelRows, int &levelColumns, int &levelNo)
{
    //Clears vectors
    levelLayout.clear();
    levelLayoutVectorStored.clear();
    
    
    //Resets rows and columns
    levelRows = 1;
    levelColumns = 0;
    
    std::ifstream inputFile;
    
    
    //Determines which level is loaded
    if(levelNo == 1)
    {
        inputFile.open(resourcePath() + "levels/level1.txt");
    }
    else if(levelNo == 2)
    {
        inputFile.open(resourcePath() + "levels/level2.txt");
    }
    else if(levelNo == 3)
    {
        inputFile.open(resourcePath() + "levels/level3.txt");
    }
    else
    {
        return;
    }
    
    //Loads all characters into levelLayout. 'f' is used as the finishing character for the text file.
    if (inputFile.is_open()) {
        char data;
        while(!inputFile.eof())
        {
            inputFile>>data;
            
            if(data == 'e' || data == 'f')
            {
                std::cout<<std::endl;
            }
            else
            {
                std::cout<<data;
            }
            if(data != 'f')
                levelLayout.push_back(data);
        }
        inputFile.close();
        
    }
    
    //Calculating size of 2D array.
    //When 'e' is hit, it denotes that there is one row below, adding to the levelRows.
    int tempColumn = 0;
    
    for(int i = 0; i < levelLayout.size(); i++){
        char character = levelLayout.at(i);
        if(character == 'e')
        {
            levelRows++;
            tempColumn = 0;
        }
        else
        {
            tempColumn++;
            if(tempColumn > levelColumns){
                levelColumns = tempColumn;
            }
        }
    }
    
    
    
    for(int i = 0; i < levelLayout.size(); i++){
        std::cout << levelLayout.at(i);
        
    }
    std::cout <<""<<std::endl;
    
    
    
    std::cout << "LevelRows: " << levelRows << std::endl;
    std::cout << "LevelColumns: " << levelColumns << std::endl;
    //Extra column ensures it doesn't break the layout.
    levelColumns++;
    
    //Creation of 2D Array based on the rows and columns calculated to ensure it's of proper size.
    char levelLayoutArray[levelRows][levelColumns];
    
    levelLayoutVectorStored.resize(levelRows);
    for (int i = 0; i < levelRows; ++i)
        levelLayoutVectorStored[i].resize(levelColumns);
    
    //Iterator int is used to iterate through levelLayout
    int iteratorOfVector = 0;
    
    //Assignment of characters to the 2D array
    for(int i = 0; i < levelRows; i++)
    {
        for(int j = 0; j < levelColumns; j++)
        {
            char currentChar = levelLayout[iteratorOfVector];
            if(currentChar != 'e' || currentChar != 'f'){
                levelLayoutArray[i][j] = currentChar;
                levelLayoutVectorStored[i][j]=currentChar;
                
                
                
            }
            iteratorOfVector++;
        }
    }
    
    //This stops the finishing character from being eaten. Unsure as to why but without it, finishing character turns to 'H' instead. Only matters for editing purposes.
    levelLayoutVectorStored[levelRows-1][levelColumns-1] = 'f';
}

//Function for loading a new level.
void loadLevel(std::vector<char> &levelLayout, std::vector<CollisionPlatform> &platforms, std::vector<TimeExtension> &timeExtensions,std::vector<TimeRemover> &timeRemovers, int &levelRows, int &levelColumns, Player &player, Goal &goal, int &levelNo){


    //Clears vectors
    levelLayout.clear();
    platforms.clear();
    timeExtensions.clear();
    timeRemovers.clear();
    levelLayoutVectorStored.clear();
    //Resets rows and columns
    levelRows = 1;
    levelColumns = 0;

    std::ifstream inputFile;


    //Determines which level is loaded
    if(levelNo == 1)
        {
            inputFile.open(resourcePath() + "levels/level1.txt");
        }
    else if(levelNo == 2)
        {
            inputFile.open(resourcePath() + "levels/level2.txt");
        }
        else if(levelNo == 3)
        {
            inputFile.open(resourcePath() + "levels/level3.txt");
        }
        else
            {
                return;
            }

    //Loads all characters into levelLayout. 'f' is used as the finishing character for the text file.
    if (inputFile.is_open()) {
      char data;
      while(!inputFile.eof())
        {
            inputFile>>data;

            if(data == 'e' || data == 'f')
                {
                    std::cout<<std::endl;
                }
            else
            {
                    std::cout<<data;
            }
            if(data != 'f')
            levelLayout.push_back(data);
        }
      inputFile.close();

    }

    //Calculating size of 2D array.
    //When 'e' is hit, it denotes that there is one row below, adding to the levelRows.
    int tempColumn = 0;

    for(int i = 0; i < levelLayout.size(); i++){
        char character = levelLayout.at(i);
            if(character == 'e')
                {
                    levelRows++;
                    tempColumn = 0;
                }
                else
                    {
                        tempColumn++;
                        if(tempColumn > levelColumns){
                        levelColumns = tempColumn;
                        }
                    }
    }

    //Cutting off finishing characters from vector.
    //For some reason, 'f' is read in twice rather than once. This cuts these characters off at the end.

    levelLayout.erase(levelLayout.end()-1);
    levelLayout.erase(levelLayout.end()-1);


    for(int i = 0; i < levelLayout.size(); i++){
        std::cout << levelLayout.at(i);

    }
    std::cout <<""<<std::endl;



    std::cout << "LevelRows: " << levelRows << std::endl;
    std::cout << "LevelColumns: " << levelColumns << std::endl;
    //Extra column ensures it doesn't break the layout.
    levelColumns++;

    //Creation of 2D Array based on the rows and columns calculated to ensure it's of proper size.
    char levelLayoutArray[levelRows][levelColumns];
    
    levelLayoutVectorStored.resize(levelRows);
    for (int i = 0; i < levelRows; ++i)
        levelLayoutVectorStored[i].resize(levelColumns);

    //Iterator int is used to iterate through levelLayout
    int iteratorOfVector = 0;

    //Assignment of characters to the 2D array
    for(int i = 0; i < levelRows; i++)
        {
            for(int j = 0; j < levelColumns; j++)
                {
                    char currentChar = levelLayout[iteratorOfVector];
                    if(currentChar != 'e' || currentChar != 'f'){
                    levelLayoutArray[i][j] = currentChar;
                        levelLayoutVectorStored[i][j]=currentChar;
                        
                       
                        
                    }
                     iteratorOfVector++;
                }
        }

        //Instantiation and placement of different objects based on the contents of the 2D array.

 for(int i = 0; i < levelRows; i++)
        {
            for(int j = 0; j < levelColumns; j++)
                {
                    if(levelLayoutArray[i][j] == '1')
                        {
                            CollisionPlatform platformI(j * 62, i * 62);
                            platforms.push_back(platformI);
                        }
                    else if(levelLayoutArray[i][j] == '2')
                        {
                            //playerSpawnX = j * 62;
                            //playerSpawnY = i * 62;
                            player.setPosition(j*62, i*62);
                        }
                    else if(levelLayoutArray[i][j] == '3')
                        {
                            //goalSpawnX = j * 62;
                            //goalSpawnY = i * 62;
                            goal.setPosition(j*62, i*62);
                        }
                    else if(levelLayoutArray[i][j] == '4')
                        {
                            TimeExtension timeExtensionI(j * 62, i * 62);
                            timeExtensions.push_back(timeExtensionI);
                        }
                    else if(levelLayoutArray[i][j] == '5')
                        {
                            TimeRemover timeRemoverI(j * 62, i * 62);
                            timeRemovers.push_back(timeRemoverI);
                        }
                }
        }
    }
