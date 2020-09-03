#include "cMain.h"
#include <string>

using namespace std;

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(32763, OnResetButtonClicked)		// Game Reset Button
	EVT_BUTTON(32764, OnGameDescButtonClicked)		// Game Description Button
	EVT_BUTTON(32765, OnGameLevelButtonClicked)		// Level Change Button
	EVT_BUTTON(32766, OnExitButtonClicked)		// Exit Button
	EVT_LEFT_DOWN(cMain::onLeftMouseDrag)	// Draggable Sources (Pieces)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Double Down",
	wxPoint(30, 30), wxSize(1300, 800))//, wxNO_BORDER)
{
	SetIcon(wxIcon(wxT("icon.ico")));	// Set Executable Icon @ Taskbar / Task Manager
	SetIcon(wxICON(frame_icon));		// Set Frame Title Icon @ Top Left of Page

	// COLORS
	wxColour white = wxColour(255, 255, 255);
	wxColour windowsBlue = wxColour(0, 162, 237);
	wxColour fire = wxColour(255, 69, 0);
	wxColour metal = wxColour(53, 55, 56);

	// FONTS
	wxFont labelFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont subLabelFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont textCtrlFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false);

	// Set cMain wxFrame style
	SetBackgroundColour(metal);
	SetBackgroundStyle(wxBG_STYLE_COLOUR);

	// SIZERS
	mainContainer = new wxBoxSizer(wxVERTICAL);

	gameContainer = new wxBoxSizer(wxHORIZONTAL);
	gameBoardContainer = new wxBoxSizer(wxVERTICAL);
	piecesContainer = new wxBoxSizer(wxVERTICAL);

	gameInfoContainer = new wxBoxSizer(wxVERTICAL);

	gameSettingsContainer = new wxBoxSizer(wxVERTICAL);
	gameSettingsButtonsContainer = new wxBoxSizer(wxHORIZONTAL);

	// LABELS
	wxStaticText* gameBoardLabel = new wxStaticText(this, wxID_ANY, "Game Board",
		wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	decorateWidget(gameBoardLabel, labelFont, white, windowsBlue);

	wxStaticText* piecesLabel = new wxStaticText(this, wxID_ANY, "Available Pieces",
		wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	decorateWidget(piecesLabel, labelFont, white, windowsBlue);

	wxStaticText* settingsLabel = new wxStaticText(this, wxID_ANY, "  Game Settings",
		wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	decorateWidget(settingsLabel, labelFont, white, windowsBlue);

	// BUTTONS
	resetGame = new wxButton(this, 32763, "Reset Game", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	decorateButton(resetGame, subLabelFont);

	gameDesc = new wxButton(this, 32764, "Game Description", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	decorateButton(gameDesc, subLabelFont);

	levelBtn = new wxButton(this, 32765, "Win Checking Lvl. 1", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	decorateButton(levelBtn, subLabelFont);

	exitBtn = new wxButton(this, 32766, "Exit Game", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	decorateButton(exitBtn, subLabelFont);

	// TEXTUAL OUTPUT CONTROL
	gameMessages = new wxRichTextCtrl(this, wxID_ANY, "", 
											  wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxNO_BORDER);
	decorateWidget(gameMessages, labelFont, white, metal);
	gameMessages->BeginTextColour(white);

	// Game Board and Piece Picker
	buildGraphicalGameBoard(labelFont, white, metal);
	buildGraphicalPiecePicker(labelFont, white, metal);

	// Add all wxControls to Correct Sizers, Add Sizers to Parent Sizers, Set Main Sizer
	gameBoardContainer->Add(gameBoardLabel, 0, wxEXPAND | wxBOTTOM, 8);
	gameBoardContainer->Add(gameBoard, 1, wxEXPAND);

	piecesContainer->Add(piecesLabel, 0, wxEXPAND | wxBOTTOM, 4);
	piecesContainer->Add(piecePicker, 1, wxEXPAND);

	gameContainer->Add(gameBoardContainer, 1, wxEXPAND | wxALL, 10);
	gameContainer->Add(piecesContainer, 1, wxEXPAND | wxALL, 10);

	gameInfoContainer->Add(gameMessages, 1, wxEXPAND);

	gameSettingsButtonsContainer->Add(resetGame, 1, wxEXPAND | wxALL, 10);
	gameSettingsButtonsContainer->Add(gameDesc, 1, wxEXPAND | wxALL, 10);
	gameSettingsButtonsContainer->Add(levelBtn, 1, wxEXPAND | wxALL, 10);
	gameSettingsButtonsContainer->Add(exitBtn, 1, wxEXPAND | wxALL, 10);

	gameSettingsContainer->Add(settingsLabel, 0, wxEXPAND | wxALL, 5);
	gameSettingsContainer->Add(gameSettingsButtonsContainer, 0, wxEXPAND);

	mainContainer->Add(gameContainer, 3, wxEXPAND);
	mainContainer->Add(gameInfoContainer, 2, wxEXPAND);
	mainContainer->Add(gameSettingsContainer, 1, wxEXPAND);

	SetSizer(mainContainer);

	Centre();

	// Print game entry messages to start the game!
	printNewMessage(wxString("\tWelcome to Double Down!"));
	printPlayerMoveInstruction();

}

cMain::~cMain()
{
	// Clean up dynamic arrays
	delete[]gameSquares;
	delete[]gamePieces;
}

// ******************************* Signatures for Styling Controls *********************************

void cMain::decorateWidget(wxControl* widget, wxFont font, wxColour wxFgColour, wxColour wxBgColor)
{
	widget->SetFont(font);
	widget->SetForegroundColour(wxFgColour);
	widget->SetBackgroundColour(wxBgColor);
}

void cMain::decorateButton(wxButton* btn, wxFont font) {
	btn->SetFont(font);
	btn->SetCursor(wxCURSOR_HAND);
}

// ******************************* Print Signatures Defined *********************************

void cMain::printNewlines(int numNewlines) {
	for(int i = 0; i < numNewlines; i++)
		gameMessages->Newline();
}

void cMain::printNewMessage(wxString str) {
	gameMessages->Clear();
	printNewlines(1);
	gameMessages->WriteText(str);
	printNewlines(1);
}

void cMain::printPlayerMoveInstruction() {
	printNewlines(1);
	(moveNum % 2 != 0) ?
		gameMessages->WriteText(wxString::Format("\t%d.  Player 1 play the piece Player 2 chooses for you.", moveNum)) :
		gameMessages->WriteText(wxString::Format("\t%d.  Player 2 play the piece Player 1 chooses for you.", moveNum));
}

void cMain::printWinner() {
	gameMessages->Clear();
	printNewlines(1);
	( (moveNum - 1) % 2 != 0) ?
		gameMessages->WriteText(wxString("\tPlayer 1 wins!!!")) :
		gameMessages->WriteText(wxString("\tPlayer 2 wins!!!"));
	levelBtn->Enable(false);
	// Hightligh the winning squares for visual feedback of a win
	for (int i = 0; i < 4; i++) {										// this color is apple green
		gameSquares[winFinder->winningIndeces[i]]->SetBackgroundColour(wxColour(130, 197, 156));
	}
}

// ******************************* Game Management Functions *********************************

/* Create Game Board:
 *	=> A grid of buttons; We iterate it with a 2D mindset,
 *	   but store the buttons in a 1D array of buttons w/ a hash
 *	=> HASH: currentRow * numberOfRows + currentColumn = index in 1D arr
 */
void cMain::buildGraphicalGameBoard(wxFont font, wxColour fg, wxColour bg) {
	// Clear existing board structures, if there are any
	gameBoard = new wxGridSizer(nRows, nCols, 0, 0);
	gameSquares = new wxButton * [nRows * nCols];
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			gameSquares[j * nRows + i] = new wxButton(this, 20000 + (j * nRows + i), "");
			decorateWidget(gameSquares[j * nRows + i], font, fg, bg);
			DropTarget* dropTarget = new DropTarget(*gameSquares[j * nRows + i]);
			gameSquares[j * nRows + i]->SetDropTarget(dropTarget);
			gameBoard->Add(gameSquares[j * nRows + i], 1, wxEXPAND | wxALL, -3);
		}
	}
}

/* Create Piece Picker:
 *	=> A grid of pieces; We iterate it with a 2D mindset,
 *	   but store the buttons in a 1D array of buttons w/ a hash
 *	=> HASH: currentRow * numberOfRows + currentColumn = index in 1D arr
 */
void cMain::buildGraphicalPiecePicker(wxFont font, wxColour fg, wxColour bg) {
	// Clear existing piece picker structures, if there are any
	piecePicker = new wxGridSizer(nRows, nCols, 0, 0);
	gamePieces = new wxButton * [nRows * nCols];
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			gamePieces[j * nRows + i] = new wxButton(this, 10000 + (j * nRows + i), pieces[j * nRows + i]);
			decorateButton(gamePieces[j * nRows + i], font);
			gamePieces[j * nRows + i]->SetCursor(wxCURSOR_HAND);
			gamePieces[j * nRows + i]->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&cMain::onLeftMouseDrag, 0, this);
			piecePicker->Add(gamePieces[j * nRows + i], 1, wxEXPAND | wxALL, 5);
		}
	}
}

void cMain::resetBoardSquares() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			gameSquares[j * nRows + i]->Enable(true);
			gameSquares[j * nRows + i]->SetLabel("");
			gameSquares[j * nRows + i]->SetBackgroundColour(wxColour(53, 55, 56));
		}
	}
}

void cMain::clearBoardString() {
	for (int i = 0; i < 16; i++) {
		boardString[i] = '.';
	}
}

void cMain::updateBoardString() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			if (gameSquares[j * nRows + i]->GetLabel() != "")
				boardString[j * nRows + i] = wxString(gameSquares[j * nRows + i]->GetLabel())[0];
		}
	}
}

void cMain::clearGamePieces() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			gamePieces[j * nRows + i]->SetLabel("");
		}
	}
}

void cMain::resetGamePieces() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			gamePieces[j * nRows + i]->SetLabel(pieces[j * nRows + i]);
		}
	}
}

void cMain::changeGameLevel() {
	if (gamePlayLevel == 1) { // If it is level 1, switch game to level 2
		gamePlayLevel = 2;
		levelBtn->SetLabel("Win Checking Lvl. 2");
	}
	else {					  // If it is level 2, switch game to level 1
		gamePlayLevel = 1;
		levelBtn->SetLabel("Win Checking Lvl. 1");
	}
}

void cMain::resetGameLevelAndButton() {
	// Ensure level button enabled
	levelBtn->Enable(true);
	// Changing the game level to two will ensure that the next function call,
	// changeGameLevel(), sets the level and button text to 1!
	gamePlayLevel = 2; 
	changeGameLevel();
}

// ******************************* Mouse Click / Drag Signatures Defined *********************************

void cMain::OnResetButtonClicked(wxCommandEvent& evt) {
	// Reset Graphical Components
	resetBoardSquares();
	resetGamePieces();
	resetGameLevelAndButton();
	// Reset Necessary Game Internals
	clearBoardString();
	moveNum = 1;
	// Update the players on reset
	printNewMessage(wxString("\tThe game has been reset!"));
	printPlayerMoveInstruction();
}

void cMain::OnGameDescButtonClicked(wxCommandEvent& evt) {
	wxMessageBox(
		"Welcome to the game of DoubleDown, where you try to complete a set of\n"
		"four pieces that are alike. Players take turns making moves. On each\n"
		"move your OPPONENT chooses the piece, then YOU get to place it on the\n"
		"board.\n\n"

		"If you create a set of four alike when you place your piece, then\n"
		"you win! A set of four alike can be completed by using four upper case\n"
		"characters, four lower-case characters, four vowels (a,e,i,o,u) or four\n"
		"consonants.\n\n"

		"The game level determines which positions can be used in completing four\n"
		"alike pieces.  Level one checks for four alike in every row, column, and\n"
		"diagonal. Level two additionally checks for the pieces in the four corners\n"
		"as well as each cluster of four in each corner.\n\n",
		"Author: Anthony Makis\n"
	);
}

void cMain::OnGameLevelButtonClicked(wxCommandEvent& evt) {
	changeGameLevel();
	updateBoardString();
	winFinder = new WinChecker(gamePlayLevel, boardString);
	if (winFinder->checkWinners()) {
		printNewMessage(wxString::Format("\tCannot Change Game Level (Leads to an old win)!", gamePlayLevel));
		printPlayerMoveInstruction();
		changeGameLevel();
	} else {
		printNewMessage(wxString::Format("\tThe win checking was just changed to level %d!", gamePlayLevel));
		printPlayerMoveInstruction();
	}
	delete winFinder;
}

void cMain::OnExitButtonClicked(wxCommandEvent& evt) {
	Close();
}

void cMain::onLeftMouseDrag(wxMouseEvent& evt)
{
	// If the id of one of the Pieces (wxStaticText) was just clicked,
	// then start to drag drop its label; otherwise, do nothing.
	if (evt.GetId() > 9999 && evt.GetId() < 20000) {
		int textSrcClicked = evt.GetId() - 10000;
		if (gamePieces[textSrcClicked]->GetLabelText() != "") { // If drag source label is not empty
			wxTextDataObject dragData(gamePieces[textSrcClicked]->GetLabelText());
			wxDropSource dragSource(*gamePieces);
			dragSource.SetData(dragData);

			wxDragResult result = dragSource.DoDragDrop();

			switch (result) {
				case wxDragCopy: // If piece copied successfully . . .
					// . . . remove piece from play
					moveNum++;
					gameMessages->Clear();
					printPlayerMoveInstruction();
					gamePieces[textSrcClicked]->SetLabel("");
					updateBoardString();
					winFinder = new WinChecker(gamePlayLevel, boardString);
					if (winFinder->checkWinners()) {
						printWinner();
						clearGamePieces();
					}
					delete winFinder; // Clean up winFinder
					break;
				default:
					break;
			}
		}
	}
}

// ******************************* Drop Target Signatures Defined *********************************

cMain::DropTarget::DropTarget(wxButton& dropTarget) : m_dropTarget(dropTarget)
{
}

bool cMain::DropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	m_dropTarget.SetLabel(data);
	m_dropTarget.Enable(false);
	return true;
}