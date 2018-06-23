/*
 * Copyright 2015-2016 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui/widget/TextWidget.h"

#include "core/Core.h"
#include "graphics/font/Font.h"
#include "gui/Text.h"
#include "scene/GameSound.h"

TextWidget::TextWidget(Font * font, const std::string & text, Vec2f pos)
	: m_font(font)
	, m_display(Automatic)
{
	m_rect = Rectf(RATIO_2(pos), 0.f, 0.f);
	setText(text);
}

void TextWidget::setText(const std::string & text) {
	m_text = text;
	Vec2i textSize = m_font->getTextSize(m_text);
	m_rect = Rectf(m_rect.topLeft(), textSize.x + 1, textSize.y + 1);
}

bool TextWidget::click() {
	
	bool result = Widget::click();
	
	if(!m_enabled) {
		return result;
	}
	
	ARX_SOUND_PlayMenu(SND_MENU_CLICK);
	
	if(clicked) {
		clicked(this);
	}
	
	return result;
}

bool TextWidget::doubleClick() {
	
	bool result = Widget::click();
	
	if(m_enabled) {
		if(doubleClicked) {
			doubleClicked(this);
		} else if(clicked) {
			clicked(this);
		}
	}
	
	return result;
}

void TextWidget::render(bool mouseOver) {
	
	Color color = Color(232, 204, 142);
	bool hasAction = m_targetMenu != NOP || clicked || doubleClicked;
	bool dynamic =  m_display == Dynamic || (m_display == Automatic && hasAction);
	if(m_display == Disabled || (dynamic && !m_enabled)) {
		color = Color::grayb(127);
	} else if(m_display == MouseOver || (dynamic && mouseOver)) {
		color = Color::white;
	}
	
	ARX_UNICODE_DrawTextInRect(m_font, m_rect.topLeft(), m_rect.right, m_text, color, NULL);
	
}
