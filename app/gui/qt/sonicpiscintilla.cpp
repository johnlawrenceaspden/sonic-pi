//--
// This file is part of Sonic Pi: http://sonic-pi.net
// Full project source: https://github.com/samaaron/sonic-pi
// License: https://github.com/samaaron/sonic-pi/blob/master/LICENSE.md
//
// Copyright 2013, 2014 by Sam Aaron (http://sam.aaron.name).
// All rights reserved.
//
// Permission is granted for use, copying, modification, distribution,
// and distribution of modified versions of this work as long as this
// notice is included.
//++

#include "sonicpiscintilla.h"

#include <QSettings>
#include <QShortcut>

#include <Qsci/qscicommandset.h>
#include <Qsci/qscilexer.h>

SonicPiScintilla::SonicPiScintilla(SonicPiLexer *lexer)
  : QsciScintilla()
{
  this->standardCommands()->clearKeys();
  this->standardCommands()->clearAlternateKeys();
  QString skey;
  QSettings settings("sonic-pi.net", "Key bindings");

#if defined(Q_OS_MAC)
  int SPi_CTRL = Qt::META;
  int SPi_META = Qt::CTRL;
#else
  int SPi_CTRL = Qt::CTRL;
  int SPi_META = Qt::ALT;
#endif

  // basic navigation
  addKeyBinding(settings, QsciCommand::PageDown, Qt::Key_PageDown);
  addKeyBinding(settings, QsciCommand::PageUp, Qt::Key_PageUp);

  addKeyBinding(settings, QsciCommand::LineDown, Qt::Key_N | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::LineDown, Qt::Key_Down);
  addKeyBinding(settings, QsciCommand::LineDownExtend, Qt::Key_Down | Qt::SHIFT);
  addKeyBinding(settings, QsciCommand::LineUp, Qt::Key_P | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::LineUp, Qt::Key_Up);
  addKeyBinding(settings, QsciCommand::LineUpExtend, Qt::Key_Up | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::CharRight, Qt::Key_F | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::CharRight, Qt::Key_Right);
  addKeyBinding(settings, QsciCommand::CharRightExtend, Qt::Key_Right | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::WordRight, Qt::Key_F | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::WordRight, Qt::Key_Right | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::WordRightExtend, Qt::Key_Right | SPi_CTRL | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::CharLeft, Qt::Key_B | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::CharLeft, Qt::Key_Left);
  addKeyBinding(settings, QsciCommand::CharLeftExtend, Qt::Key_Left | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::WordLeft, Qt::Key_B | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::WordLeft, Qt::Key_Left | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::WordLeftExtend, Qt::Key_Left | SPi_CTRL | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::Delete, Qt::Key_D | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::Delete, Qt::Key_Delete);

  addKeyBinding(settings, QsciCommand::DeleteBack, Qt::Key_H | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::DeleteBack, Qt::Key_Backspace);

  addKeyBinding(settings, QsciCommand::Home, Qt::Key_A | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::VCHome, Qt::Key_Home);
  addKeyBinding(settings, QsciCommand::VCHomeExtend, Qt::Key_Home | Qt::SHIFT);
  addKeyBinding(settings, QsciCommand::DocumentStart, Qt::Key_Home | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::DocumentStartExtend, Qt::Key_Home | SPi_CTRL | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::LineEnd, Qt::Key_E | SPi_CTRL);
  addOtherKeyBinding(settings, QsciCommand::LineEnd, Qt::Key_End);
  addKeyBinding(settings, QsciCommand::LineEndExtend, Qt::Key_End | Qt::SHIFT);
  addKeyBinding(settings, QsciCommand::DocumentEnd, Qt::Key_End | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::DocumentEndExtend, Qt::Key_End | SPi_CTRL | Qt::SHIFT);

  addKeyBinding(settings, QsciCommand::Delete, Qt::Key_D | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::VerticalCentreCaret, Qt::Key_L | SPi_CTRL);

  // tab return
  addKeyBinding(settings, QsciCommand::Newline, Qt::Key_Return);

  addKeyBinding(settings, QsciCommand::Backtab, Qt::Key_Tab | Qt::SHIFT);

  // copy paste
  addKeyBinding(settings, QsciCommand::SelectionCut, Qt::Key_X | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::SelectionCut, Qt::Key_X | SPi_CTRL);

  addKeyBinding(settings, QsciCommand::Paste, Qt::Key_V | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::Paste, Qt::Key_Y | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::Undo, Qt::Key_Z | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::Undo, Qt::Key_Z | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::Redo, Qt::Key_Z | Qt::SHIFT | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::Redo, Qt::Key_Z | Qt::SHIFT | SPi_CTRL);
  addKeyBinding(settings, QsciCommand::SelectAll, Qt::Key_A | SPi_META);

  this->standardCommands()->readSettings(settings);

  this->setMatchedBraceBackgroundColor(QColor("dimgray"));
  this->setMatchedBraceForegroundColor(QColor("white"));

  this->setIndentationWidth(2);
  this->setIndentationGuides(true);
  this->setIndentationGuidesForegroundColor(QColor("deep pink"));
  this->setBraceMatching( SonicPiScintilla::SloppyBraceMatch);

  //TODO: add preference toggle for this:
  //this->setFolding(SonicPiScintilla::CircledTreeFoldStyle, 2);
  this->setCaretLineVisible(true);
  this->setCaretLineBackgroundColor(QColor("whitesmoke"));
  this->setFoldMarginColors(QColor("whitesmoke"),QColor("whitesmoke"));
  this->setMarginLineNumbers(0, true);
  this->setMarginsBackgroundColor(QColor("whitesmoke"));
  this->setMarginsForegroundColor(QColor("dark gray"));
  this->setMarginsFont(QFont("Menlo", 15, -1, true));
  this->setUtf8(true);
  this->setText("#loading...");
  this->setLexer((QsciLexer *)lexer);

  this->setAutoCompletionThreshold(1);
  this->setAutoCompletionSource(SonicPiScintilla::AcsAPIs);
  this->setAutoCompletionCaseSensitivity(false);

  this->setSelectionBackgroundColor("DeepPink");
  this->setSelectionForegroundColor("white");
  this->setCaretWidth(5);
  this->setCaretForegroundColor("deep pink");
  this->setEolMode(EolUnix);

  addKeyBinding(settings, QsciCommand::SelectionCopy, Qt::Key_C | SPi_META);
  addOtherKeyBinding(settings, QsciCommand::SelectionCopy, Qt::Key_C | SPi_CTRL);

}

void SonicPiScintilla::hideLineNumbers(){
  this->setMarginLineNumbers(0, false);
  this->setMarginWidth(0, "0");
  SendScintilla(SCI_HIDELINES);
}

void SonicPiScintilla::showLineNumbers(){
  this->setMarginLineNumbers(0, true);
  this->setMarginWidth(0, "1000");
  SendScintilla(SCI_SHOWLINES);
}

void SonicPiScintilla::addOtherKeyBinding(QSettings &qs, int cmd, int key)
{
  QString skey;
  skey.sprintf("/Scintilla/keymap/c%d/alt", cmd);
  qs.setValue(skey, key);
}

void SonicPiScintilla::addKeyBinding(QSettings &qs, int cmd, int key)
{
  QString skey;
  skey.sprintf("/Scintilla/keymap/c%d/key", cmd);
  qs.setValue(skey, key);
}

void SonicPiScintilla::cutLineFromPoint()
{
  int linenum, index;
  getCursorPosition(&linenum, &index);

  if (text(linenum) == "\n")
  {
    setSelection(linenum, index, linenum + 1, 0);
    SendScintilla(SCI_CUT);
  } else
    {
      //  SendScintilla(SCI_CLEARSELECTIONS);
      int pos = SendScintilla(SCI_GETCURRENTPOS);
      SendScintilla(SCI_LINEEND);
      SendScintilla(SCI_SETANCHOR, pos);
      SendScintilla(SCI_CUT);
    }
}

void SonicPiScintilla::tabCompleteifList()
{
  if(isListActive())
    {
      SendScintilla(QsciCommand::Tab);
    }
}

void SonicPiScintilla::transposeChars()
{
  int linenum, index;
  getCursorPosition(&linenum, &index);
  setSelection(linenum, 0, linenum + 1, 0);
  int lineLength = selectedText().size();

  //transpose chars
  if(index > 0){
    if(index < (lineLength - 1)){
      index = index + 1;
    }
    setSelection(linenum, index - 2, linenum, index);
    QString text = selectedText();
    QChar a, b;
    a = text.at(0);
    b = text.at(1);
    QString replacement  = "";
    replacement.append(b);
    replacement.append(a);
    replaceSelectedText(replacement);
  }

  setCursorPosition(linenum, index);
}

void SonicPiScintilla::setMark()
{
  int pos = SendScintilla(SCI_GETCURRENTPOS);
  SendScintilla(SCI_SETEMPTYSELECTION, pos);
  SendScintilla(SCI_SETSELECTIONMODE, 0);
}

void SonicPiScintilla::escapeAndCancelSelection()
{
  int pos = SendScintilla(SCI_GETCURRENTPOS);
  SendScintilla(SCI_SETEMPTYSELECTION, pos);
  SendScintilla(SCI_CANCEL);
}

void SonicPiScintilla::copyClear()
{
  QsciScintilla::copy();
  int pos = SendScintilla(SCI_GETCURRENTPOS);
  SendScintilla(SCI_SETEMPTYSELECTION, pos);
}

void SonicPiScintilla::replaceLine(int lineNumber, QString newLine)
{
  setSelection(lineNumber, 0, lineNumber + 1, 0);
  replaceSelectedText(newLine);
}

void SonicPiScintilla::replaceLines(int lineStart, int lineFinish, QString newLines)
{
  setSelection(lineStart, 0, lineFinish + 1, 0);
  replaceSelectedText(newLines);
}

void SonicPiScintilla::forwardLines(int numLines) {
  int idx;
  if(numLines > 0) {
    for (idx = 0 ; idx < numLines ; idx++) {
      SendScintilla(SCI_LINEUP);
    }
  } else {
    for (idx = 0 ; idx > numLines ; idx--) {
      SendScintilla(SCI_LINEDOWN);
    }
  }
}

void SonicPiScintilla::forwardTenLines() {
  forwardLines(10);
}

void SonicPiScintilla::backTenLines() {
  forwardLines(-10);
}

void SonicPiScintilla::moveLineOrSelectionUp() {
  moveLineOrSelection(-1);
}

void SonicPiScintilla::moveLineOrSelectionDown() {
  moveLineOrSelection(1);
}

void SonicPiScintilla::moveLineOrSelection(int numLines) {
  beginUndoAction();

  int linenum, cursor, origLinenum, origCursor;
  getCursorPosition(&linenum, &cursor);
  origLinenum = linenum;
  origCursor = cursor;

  bool hadSelectedText = hasSelectedText();


  if(!hadSelectedText) {
    setSelection(linenum, 0, linenum + 1, 0);
  }

  int lineFrom, indexFrom, lineTo, indexTo, lineOffset;
  getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
  lineOffset = lineTo - origLinenum;
  linenum = lineFrom;

  QString selection = selectedText();

  if(selection[selection.length()-1] != '\n') {
    selection = selection + "\n";
    lineTo += 1;
    lineOffset += 1;
    indexTo = 0;
    replaceSelectedText("");
    setCursorPosition(linenum, 0);
    SendScintilla(SCI_DELETEBACK);
  } else {
    replaceSelectedText("");
  }
  setCursorPosition(linenum, 0);

  moveLines(numLines);

  getCursorPosition(&linenum, &cursor);
  setCursorPosition(linenum, 0);
  insert(selection);

  setCursorPosition(linenum + lineOffset, origCursor);

  int diffLine = lineTo - lineFrom;
  int diffIndex = indexTo - indexFrom;

  setSelection(linenum + diffLine, diffIndex, linenum, 0);

  endUndoAction();
}

QStringList SonicPiScintilla::apiContext(int pos, int &context_start,
					 int &last_word_start)
{
  QStringList context;
  // sampl|
  // sample |
  // chord :E3,|

  int linenum, cursor;
  getCursorPosition(&linenum, &cursor);
  QString line = text(linenum);
  line.truncate(cursor);
  context = line.split(QRegExp("[ ,(){}]+"));

  context_start = 0;
  last_word_start = pos;

  return context;
}

int SonicPiScintilla::incLineNumWithinBounds(int linenum, int inc) {
  linenum += inc;
  int maxBufferIndex = lines() - 1;

  if(linenum < 0) {
    linenum = 0;
  }

  if(linenum > maxBufferIndex) {
    linenum = maxBufferIndex;
  }

  return linenum;
}

void SonicPiScintilla::moveLines(int numLines) {
  if (numLines > 0)
  {
    for(int i = 0 ; i < numLines ; i++) {
      SendScintilla(SCI_LINEDOWN);
    }
  } else {
    for(int i = 0 ; i > numLines ; i--) {
      SendScintilla(SCI_LINEUP);
    }
  }
}
