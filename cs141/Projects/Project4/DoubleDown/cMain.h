#pragma once

#include "wx/wx.h"
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/dnd.h>
#include <wx/tglbtn.h>
#include <wx/richtext/richtextctrl.h>
#include "WinChecker.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	// Game and Game Board Setup:
	int nRows = 4;
	int nCols = 4;
	int gamePlayLevel = 1;
	int moveNum = 1;
	const char pieces[17] = "AEIOaeioBCDFbcdf";
	char boardString[17]  = "................";

	// Drop Targets => Game Board Squares!
	wxButton** gameSquares = nullptr;

	// Game Settings Buttons
	wxButton* resetGame = nullptr;
	wxButton* gameDesc = nullptr;
	wxButton* levelBtn = nullptr;
	wxButton* exitBtn = nullptr;

	// Game Info Rich Content Box
	wxRichTextCtrl* gameMessages = nullptr;

	// Main Sizer for Overall Game Window
	wxBoxSizer* mainContainer = nullptr;

	// Sizer for holding both Game Board and Piece Picker
	wxBoxSizer* gameContainer = nullptr;
	// Individual Sizers for the Game Board and its label, as well as for the Piece Picker and its label
	wxBoxSizer* gameBoardContainer = nullptr;
	wxBoxSizer* piecesContainer = nullptr;
	// Individual Sizers for just the Game Board or the Piece Picker
	wxGridSizer* gameBoard = nullptr;
	wxGridSizer* piecePicker = nullptr;

	// Sizer for holding the Game Information
	wxBoxSizer* gameInfoContainer = nullptr;

	// Sizer for holding the Game Settings
	wxBoxSizer* gameSettingsContainer = nullptr;
	// Sizer for holding the Game Settings Buttons
	wxBoxSizer* gameSettingsButtonsContainer = nullptr;

	WinChecker* winFinder;

	void decorateWidget(wxControl* widget, wxFont font, wxColour wxFgColour, wxColour wxBgColor);
	void decorateButton(wxButton* btn, wxFont font);

	void printPlayerMoveInstruction();
	void printNewlines(int numNewlines);
	void printWinner();

	void buildGraphicalGameBoard(wxFont font, wxColour fg, wxColour bg);
	void buildGraphicalPiecePicker(wxFont font, wxColour fg, wxColour bg);
	void resetBoardSquares();
	void clearBoardString();
	void updateBoardString();
	void clearGamePieces();
	void resetGamePieces();
	void changeGameLevel();
	void printNewMessage(wxString str);
	void resetGameLevelAndButton();

	void OnResetButtonClicked(wxCommandEvent& evt);
	void OnGameDescButtonClicked(wxCommandEvent& evt);
	void OnGameLevelButtonClicked(wxCommandEvent& evt);
	void OnExitButtonClicked(wxCommandEvent& evt);

private:
	// Necessary signatures for Drag Sources => Game Pieces!
	void onLeftMouseDrag(wxMouseEvent& evt);

	wxButton** gamePieces = nullptr; // Drag Sources

private:
	// Necessary signatures for Drop Targets => Game Board Squares!
	class DropTarget : public wxTextDropTarget
	{
	public:
		DropTarget(wxButton& dropTarget);

		virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

	private:
		wxButton& m_dropTarget;
	};

public:
	wxDECLARE_EVENT_TABLE();
};
