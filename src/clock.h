/******************************************************************************
 * $Id: clock.h, v1.0 2011/05/15 nohal Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Tactics Plugin
 * Author:   Pavel Kalian
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "instrument.h"
extern int g_iUTCOffset;    // get offset from tactics_pi.cpp

class TacticsInstrument_Clock: public TacticsInstrument_Single
{
public:
    TacticsInstrument_Clock( wxWindow *parent, wxWindowID id, wxString title, int cap_flag=OCPN_DBP_STC_CLK, wxString format=_T("%02i:%02i:%02i UTC") );

    ~TacticsInstrument_Clock(void){}

    wxSize GetSize( int orient, wxSize hint );
    void SetData(int, double, wxString);
    virtual void SetUtcTime(wxDateTime value);
    wxString GetDisplayTime( wxDateTime UTCtime );
    bool getUTC() { return bUTC; }
    void setUTC( bool flag ) { bUTC = flag; }

private:
    bool bUTC;
};

class TacticsInstrument_Moon : public TacticsInstrument_Clock
{
public:
    TacticsInstrument_Moon( wxWindow *parent, wxWindowID id, wxString title);
    ~TacticsInstrument_Moon(){}

    wxSize GetSize( int orient, wxSize hint );
    void SetData( int, double, wxString );
    void Draw(wxGCDC* dc);
    void SetUtcTime(wxDateTime value);

private:
    int moon_phase(int y, int m, int d);
    int m_phase;
    int m_radius;
    wxString m_hemisphere;
};

class TacticsInstrument_Sun : public TacticsInstrument_Clock
{
public:
    TacticsInstrument_Sun( wxWindow *parent, wxWindowID id, wxString title );

    ~TacticsInstrument_Sun(){}

    wxSize GetSize( int orient, wxSize hint );
    void Draw(wxGCDC* dc);
    void SetData( int st, double data, wxString unit );
    void SetUtcTime( wxDateTime value );

private:
    wxString m_sunrise;
    wxString m_sunset;
    double m_lat;
    double m_lon;
    wxDateTime m_dt;

    void calculateSun( double latit, double longit, wxDateTime &sunrise, wxDateTime &sunset );
};

class TacticsInstrument_CPUClock : public TacticsInstrument_Clock
{
public:
    TacticsInstrument_CPUClock( wxWindow *parent, wxWindowID id, wxString title, wxString format = _T( "%02i:%02i:%02i UTC" ) );

    ~TacticsInstrument_CPUClock() {}

    void SetData( int, double, wxString );

    void SetUtcTime( wxDateTime value );
};
#endif // __CLOCK_H__

