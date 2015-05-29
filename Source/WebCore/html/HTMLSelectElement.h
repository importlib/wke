/*
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2004, 2005, 2006, 2007, 2009, 2010, 2011 Apple Inc. All rights reserved.
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef HTMLSelectElement_h
#define HTMLSelectElement_h

#include "CollectionCache.h"
#include "Event.h"
#include "HTMLFormControlElement.h"
#include <wtf/Vector.h>

namespace WebCore {

class HTMLOptionElement;
class HTMLOptionsCollection;

class HTMLSelectElement : public HTMLFormControlElementWithState {
public:
    static PassRefPtr<HTMLSelectElement> create(const QualifiedName&, Document*, HTMLFormElement*);

    int selectedIndex() const;
    void setSelectedIndex(int index, bool deselect = true);
    void setSelectedIndexByUser(int index, bool deselect = true, bool fireOnChangeNow = false, bool allowMultipleSelection = false);

    // For ValidityState
    bool valueMissing() const;

    unsigned length() const;

    int size() const { return m_size; }
    bool multiple() const { return m_multiple; }

    void add(HTMLElement*, HTMLElement* beforeElement, ExceptionCode&);
    void remove(int index);
    void remove(HTMLOptionElement*);

    String value() const;
    void setValue(const String&);

    PassRefPtr<HTMLOptionsCollection> options();

    void optionElementChildrenChanged();

    void setRecalcListItems();
    void updateListItemSelectedStates();

    const Vector<HTMLElement*>& listItems() const;

    virtual void accessKeyAction(bool sendToAnyElement);
    void accessKeySetSelectedIndex(int);

    void setMultiple(bool);

    void setSize(int);

    void setOption(unsigned index, HTMLOptionElement*, ExceptionCode&);
    void setLength(unsigned, ExceptionCode&);

    Node* namedItem(const AtomicString& name);
    Node* item(unsigned index);

    CollectionCache* collectionInfo() { m_collectionInfo.checkConsistency(); return &m_collectionInfo; }

    void scrollToSelection();

    bool canSelectAll() const;
    void selectAll();
    int listToOptionIndex(int listIndex) const;
    void listBoxOnChange();
    int optionToListIndex(int optionIndex) const;
    int activeSelectionStartListIndex() const;
    int activeSelectionEndListIndex() const;
    void setActiveSelectionAnchorIndex(int);
    void setActiveSelectionEndIndex(int);
    void updateListBoxSelection(bool deselectOtherOptions);
    
protected:
    HTMLSelectElement(const QualifiedName&, Document*, HTMLFormElement*);

private:
    virtual const AtomicString& formControlType() const;
    
    virtual bool isKeyboardFocusable(KeyboardEvent*) const;
    virtual bool isMouseFocusable() const;

    virtual void dispatchFocusEvent(PassRefPtr<Node> oldFocusedNode);
    virtual void dispatchBlurEvent(PassRefPtr<Node> newFocusedNode);
    
    virtual bool canStartSelection() const { return false; }

    virtual bool isEnumeratable() const { return true; }

    virtual bool saveFormControlState(String& value) const;
    virtual void restoreFormControlState(const String&);

    virtual void parseMappedAttribute(Attribute*);

    virtual RenderObject* createRenderer(RenderArena*, RenderStyle *);
    virtual bool appendFormData(FormDataList&, bool);

    virtual void reset();

    virtual void defaultEventHandler(Event*);

    void menuListOnChange();
    
    void recalcListItems(bool updateSelectedStates = true) const;

    void deselectItems(HTMLOptionElement* excludeElement = 0);
    void typeAheadFind(KeyboardEvent*);
    void saveLastSelection();

    virtual void insertedIntoTree(bool);

    virtual bool isOptionalFormControl() const { return !isRequiredFormControl(); }
    virtual bool isRequiredFormControl() const;

    bool hasPlaceholderLabelOption() const;

    void setSelectedIndex(int optionIndex, bool deselect, bool fireOnChangeNow, bool userDrivenChange);
    void deselectItemsWithoutValidation(Element* excludeElement = 0);
    void parseMultipleAttribute(const Attribute*);
    int lastSelectedListIndex() const;
    void updateSelectedState(int listIndex, bool multi, bool shift);
    void menuListDefaultEventHandler(Event*);
    bool platformHandleKeydownEvent(KeyboardEvent*);
    void listBoxDefaultEventHandler(Event*);
    void setOptionsChangedOnRenderer();
    bool usesMenuList() const;

    enum SkipDirection {
        SkipBackwards = -1,
        SkipForwards = 1
    };
    int nextValidIndex(int listIndex, SkipDirection, int skip) const;
    int nextSelectableListIndex(int startIndex) const;
    int previousSelectableListIndex(int startIndex) const;
    int firstSelectableListIndex() const;
    int lastSelectableListIndex() const;
    int nextSelectableListIndexPageAway(int startIndex, SkipDirection) const;

    virtual void childrenChanged(bool changedByParser = false, Node* beforeChange = 0, Node* afterChange = 0, int childCountDelta = 0);

    CollectionCache m_collectionInfo;
    // m_listItems contains HTMLOptionElement, HTMLOptGroupElement, and HTMLHRElement objects.
    mutable Vector<HTMLElement*> m_listItems;
    Vector<bool> m_lastOnChangeSelection;
    Vector<bool> m_cachedStateForActiveSelection;
    DOMTimeStamp m_lastCharTime;
    String m_typedString;
    int m_size;
    int m_lastOnChangeIndex;
    int m_activeSelectionAnchorIndex;
    int m_activeSelectionEndIndex;
    UChar m_repeatingChar;
    bool m_userDrivenChange;
    bool m_multiple;
    bool m_activeSelectionState;
    mutable bool m_shouldRecalcListItems;
};

inline void HTMLSelectElement::setSelectedIndex(int index, bool deselect)
{
    setSelectedIndex(index, deselect, false, false);
}

inline bool HTMLSelectElement::usesMenuList() const
{
#if ENABLE(NO_LISTBOX_RENDERING)
    return true;
#else
    return !m_multiple && m_size <= 1;
#endif
}

HTMLSelectElement* toHTMLSelectElement(Node*);
const HTMLSelectElement* toHTMLSelectElement(const Node*);
void toHTMLSelectElement(const HTMLSelectElement*); // This overload will catch anyone doing an unnecessary cast.

#ifdef NDEBUG

// The debug versions of these, with assertions, are not inlined.

inline HTMLSelectElement* toHTMLSelectElement(Node* node)
{
    return static_cast<HTMLSelectElement*>(node);
}

inline const HTMLSelectElement* toHTMLSelectElement(const Node* node)
{
    return static_cast<const HTMLSelectElement*>(node);
}

#endif

} // namespace

#endif
