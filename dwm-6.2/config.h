#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */

static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 14;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "nerdfont:size=12" };
static const char dmenufont[]       = "nerdfont:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#dfdfdf";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#009cc7";
static const char col_purple[]      = "#9750ce";
static const char *colors[][8]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1,   col_gray2 },
	[SchemeSel]  = { col_gray4, col_purple,  col_cyan  },

	/*
	[Bat0]  = { "#a6e8a5", col_gray1,  col_cyan  },
	[Bat1]  = { "#d6ffa5", col_gray1,  col_cyan  },
	[Bat2]  = { "#ffffa5", col_gray1,  col_cyan  },
	[Bat3]  = { "#f8cda6", col_gray1,  col_cyan  },
	[Bat4]  = { "#f78272", col_gray1,  col_cyan  },
	[Purp]  = { "#b067e8", col_gray1,  col_cyan  },
	[Blue]  = { "#6ca4ed", col_gray1,  col_cyan  },
	[Pink]  = { "#f0449f", col_gray1,  col_cyan  },

*/

};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "<>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY          Mod4Mask
#define PrintScreen	    0x0000ff61
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_purple, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *slock[] = { "i3lock", "-i", "/home/kamee/dotfiles/lockscreen.png", NULL };
static const char *volumeup[]    = { "amixer", "set", "Master", "2%+", NULL };
static const char *volumedown[]  = { "amixer", "set", "Master", "2%-", NULL };
static const char *mutevol[]     = { "amixer", "set", "Master", "toggle", NULL };

static const char *brightnessup[]     = { "xbacklight", "-inc", "5", NULL };
static const char *brightnessdown[]   = { "xbacklight", "-dec", "5", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,  {.v = volumedown } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,  {.v = volumeup } },
	{ 0,                            XF86XK_AudioMute,         spawn,  {.v = mutevol } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,  {.v = brightnessup } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,  {.v = brightnessdown } },
	{ MODKEY,                       PrintScreen, spawn,        SHCMD("maim -m 10 | tee ~/screenshots/screenshot_$(date '+%Y%m-%d_%H:%M:%S').png | xclip -selection clipboard -t image/png") },
	{ 0,                            PrintScreen, spawn,        SHCMD("maim  -m 10 -s | tee ~/screenshots/screenshot_$(date '+%Y-%m-%d_%H:%M:%S').png | xclip -selection clipboard -t image/png") },
	{ MODKEY|ShiftMask,             XK_x,      quit,      	   {0} },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = slock } },
	{ MODKEY,                  		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

