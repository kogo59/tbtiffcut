/*
 *  This file is part of tbtiffcut.
 *
 *  Copyright (c) 2020 kogo <kogo@gmx.de>
 *
 *  tbtiffcut is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  tbtiffcut is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tbtiffcut.  If not, see <http://www.gnu.org/licenses/>.
 */


/*
 * tbtiffcut.h
 *
 *  Created on: 24.02.2020
 *      Author: kogo
 */

#ifndef TBTIFFCUT_H_
#define TBTIFFCUT_H_

#include <memory>
#include <wx/wx.h>


/*
 * =====================================================================================
 *        Class:  tbtiffcutApp
 *  Description:
 * =====================================================================================
 */
class tbtiffcutApp: public wxApp
{
public:
    bool OnInit() override;
  	int OnExit () override;

private:
  	void initLanguageSupport();

  	std::unique_ptr<wxLocale> locale = nullptr;

		MyTbtiffcutUI *frame;

};




#endif /* TBTIFFCUT_H_ */
