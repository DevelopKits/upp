#ifndef LAYDES_H
#define LAYDES_H

#include <ide/Common/Common.h>
#include <RichEdit/RichEdit.h>
#include <CodeEditor/CodeEditor.h>
#include <IconDes/IconDes.h>

#define LAYOUTFILE <ide/LayDes/LayDes.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS LayImg
#define IMAGEFILE  <ide/LayDes/LayDes.iml>
#include <Draw/iml_header.h>

#define KEYNAMESPACE LayoutKeys
#define KEYGROUPNAME "Layout"
#define KEYFILE      <ide/LayDes/laydes.key>
#include             <CtrlLib/key_header.h>

class DiffPacker {
	String master;
	int         mapn;
	Buffer<int> map;
	Buffer<int> prev;

public:
	void   SetMaster(const String& master);
	String Pack(const String& data);
};

String DiffPack(const String& master, const String& data);
String DiffUnpack(const String& master, const String& pack);

struct TypeProperty : Moveable<TypeProperty> {
	int    level;
	String type;
	String name;
	String defval;
	String help;

	TypeProperty() { level = 0; }
};

enum { LAYOUT_CTRL, LAYOUT_SUBCTRL, LAYOUT_TEMPLATE };

struct LayoutType : Moveable<LayoutType> {
	int                        kind;
	Array<TypeProperty>        property;
	ArrayMap<String, EscValue> methods;
	String                     group;
	Image                      icon[2];
	Size                       iconsize[2];

	LayoutType()               { iconsize[0] = iconsize[1] = Null; }
};

VectorMap<String, VectorMap<String, String> >& LayoutEnums();
VectorMap<String, LayoutType>&                 LayoutTypes();

Point ReadPoint(CParser& p);

struct EscDraw : public EscHandle {
	Draw& w;

	void DrawRect(EscEscape& e);
	void DrawLine(EscEscape& e);
	void DrawText(EscEscape& e);
	void DrawSmartText(EscEscape& e);
	void DrawQtf(EscEscape& e);
	void GetTextSize(EscEscape& e);
	void DrawImage(EscEscape& e);
	void DrawImageColor(EscEscape& e);

	typedef EscDraw CLASSNAME;

	EscDraw(EscValue& v, Draw& w);
};

EscValue EscColor(Color c);
Color    ColorEsc(EscValue v);

EscValue EscSize(Size sz);
Size     SizeEsc(EscValue v);

EscValue EscPoint(Point sz);
Point    PointEsc(EscValue v);

EscValue EscRect(const Rect& r);
Rect     RectEsc(EscValue v);

EscValue EscFont(Font f);
Font     FontEsc(EscValue v);

struct ItemProperty : public Ctrl {
	int     level;
	String  name;
	Value   defval;
	String  help;

	virtual void     Paint(Draw& w);

	virtual int      GetHeight() const;

	virtual void     SetCharset(byte charset);
	virtual void     Read(CParser& p);
	virtual String   Save() const;
	virtual bool     PlaceFocus(dword k, int c);

	ItemProperty() { NoWantFocus(); level = 0; }
	virtual ~ItemProperty() {}

	static VectorMap<String, ItemProperty *(*)()>& Factory();
	static ItemProperty *Create(const String& name);
	static void          Register(const char *name, ItemProperty *(*creator)());
};

template <class Editor>
class EditorProperty : public ItemProperty {
public:
	virtual Value    GetData() const            { return ~editor; }
	virtual bool     PlaceFocus(dword k, int c) { editor.SetFocus(); return editor.Key(k, c); }

protected:
	void EditAction()                           { this->UpdateActionRefresh(); }

	Editor editor;

	EditorProperty() {
		editor.WhenAction = callback(this, &EditorProperty::EditAction);
	}
};

String ReadPropertyParam(CParser& p);

struct RawProperty : public EditorProperty<EditString>
{
	virtual String   Save() const;
	virtual void     Read(CParser& p);

	static ItemProperty *Create()            { return new RawProperty; }

	RawProperty() {
		Add(editor.HSizePos(100, 2).TopPos(2));
	}
};

struct PropertyPane : public StaticRect {
	virtual void Layout();
	virtual void ChildGotFocus();

	int        y;
	StaticRect pane;
	ScrollBar  sb;

	void Clear();
	void Add(ItemProperty& c);
	void SetSb();
	void Scroll();
	void AfterCreate();

	typedef PropertyPane CLASSNAME;

	PropertyPane();
};

struct LayoutItem {
	String              type;
	String              variable;
	Ctrl::LogPos        pos;
	Array<ItemProperty> property;
	bool                hide;
	byte                charset;

private:
	Size      csize;
	Drawing   cache;

	void   UnknownPaint(Draw& w);
	void   CreateProperties(const String& classname, int level);
	void   CreateMethods(EscValue& ctrl, const String& type, bool copy) const;

public:
	void     Invalidate()               { csize.cx = -1; }
	EscValue CreateEsc() const;
	EscValue ExecuteMethod(const char *method, Vector<EscValue>& arg) const;
	EscValue ExecuteMethod(const char *method) const;
	Size     GetMinSize();
	Size     GetStdSize();
	void     Paint(Draw& w, Size sz, bool sample = false);
	void     Create(const String& type);
	int      FindProperty(const String& s) const;
	void     SetCharset(byte charset);
	void     ReadProperties(CParser& p, bool addunknow = true);
	String   SaveProperties() const;
	String   Save(int i) const;

	LayoutItem()                      { csize.cx = -1; hide = false; charset = CHARSET_UNICODE; }
};

Image GetTypeIcon(const String& type, int cx, int cy, int i, Color bg);

Array<LayoutItem> ReadItems(CParser& p, byte charset);

class LayoutUndo {
	Vector<String> stack;

public:
	void               Clear()                        { stack.Clear(); }
	int                GetCount() const               { return stack.GetCount(); }
	operator           bool() const                   { return stack.GetCount(); }
	void               Push(const String& state);
	const String&      Top() const                    { return stack.Top(); }
	String             Pop();
};

struct LayoutData {
	String name;
	Size   size;
	Array<LayoutItem> item;
	LayoutUndo undo, redo;
	byte charset;

private:
	String      MakeState();
	void        LoadState(const String& s);
	void        Do(LayoutUndo& u1, LayoutUndo& u2);
	String      GetTID(int i);

public:
	void        SetCharset(byte charset);
	void        Read(CParser& p);
	String      Save();
	String      Save(const Vector<int>& sel);
	void        SaveState();
	bool        IsUndo();
	void        Undo();
	bool        IsRedo();
	void        Redo();

	LayoutData() { size = Size(400, 200); charset = CHARSET_UNICODE; }
};

class LayDesigner;

struct LayDesEditPos {
	Time              filetime;
	Array<LayoutUndo> undo;
	Array<LayoutUndo> redo;
	int               layouti;
	Vector<int>       cursor;

	LayDesEditPos() { filetime = Null; }
};

class LayDes : public StaticRect {
public:
	virtual void   Paint(Draw& w);
	virtual Image  CursorImage(Point p, dword keyflags);
	virtual void   LeftDown(Point p, dword keyflags);
	virtual void   LeftRepeat(Point p, dword keyflags);
	virtual void   MouseMove(Point p, dword keyflags);
	virtual void   LeftUp(Point p, dword keyflags);
	virtual void   RightDown(Point p, dword keyflags);
	virtual void   Layout();

private:
	bool   DoKey(dword key, int count);

	struct KeyMaster : public ParentCtrl {
		LayDes *d;

		virtual bool   Key(dword key, int count) {
			return d->DoKey(key, count);
		}
	};

	String   filename;
	byte     charset;
	String   layfile;
	bool     newfile;
	Time     filetime;
	String   fileerror;

	friend class LayDesigner;

	LayDesigner       *frame;
	ToolBar            toolbar;
	MenuBar            menubar;
	ArrayCtrl          layoutlist;
	ArrayCtrl          item;
	PropertyPane       property;

	WithDropChoice<EditString> type;
	EditString                 variable;

	KeyMaster          km;
	Splitter           lsplit, isplit, rsplit;
	FrameTop<Splitter> twsplit;
	ScrollBars        sb;
	FrameRight<Label> status;

	Array<LayoutData> layout;
	int               currentlayout;

	Vector<Point>     handle;
	Vector<int>       cursor;
	int               draghandle;
	Point             dragbase;
	Size              draglayoutsize;
	Rect              dragrect;
	Vector<Rect>      itemrect;
	int               basesel;

	bool              usegrid;
	bool              ignoreminsize;

	WithMatrixLayout<TopWindow>  matrix;
	WithSettingLayout<TopWindow> setting;

	struct TempGroup {
		String temp;
		String group;
		bool operator==(const TempGroup& b) const { return temp == b.temp && group == b.group; }
		friend unsigned GetHashValue(const TempGroup& g) { return 0; }
		TempGroup(const String& temp, const String& group) : temp(temp), group(group) {}
	};

	Rect   CtrlRect(Ctrl::LogPos pos, Size sz);
	Rect   CtrlRectZ(Ctrl::LogPos pos, Size sz);
	void   AddHandle(Draw& w, int x, int y);
	Point  Normalize(Point p);
	Point  ZPoint(Point p);
	int    FindHandle(Point p);
	int    FindItem(Point p);
	void   GetSprings(Rect& l, Rect& t, Rect& r, Rect& b);
	void   DrawSpring(Draw& w, const Rect& r, bool horz, bool spring);
	void   SelectOne(int ii, dword flags);
	void   StoreItemRects();
	void   LoadItems();
	void   LoadItem(int item);
	void   ReloadItems();
	void   SyncItems();
	void   SyncItem(int item, int style);
	void   SyncProperties(bool sync);
	void   SyncLayoutList();
	void   CreateCtrl(const String& type);
	void   Group(Bar& bar, const String& group);
	void   Templates(Bar& bar);
	void   TemplateGroup(Bar& bar, TempGroup tg);
	void   Template(Bar& bar, const String& temp);
	int    ParseLayoutRef(String cls, String& base) const;
	void   PaintLayoutItems(Draw& w, int layout, Size size, Index<int>& passed, const Vector<bool>& cursor);

	void   SaveState();
	void   SetSb();

	void   FrameFocus();
	void   PropertyChanged();

	void   SetBar();
	void   Scroll();

	void   SetStatus(bool down = false);

	void        Flush();
	LayoutData& CurrentLayout();
	void        LayoutCursor();

	LayoutItem& CurrentItem();
	void        ItemClick();

	String      SaveSelection();
	LayoutData  LoadLayoutData(const String& s);

	void        Undo();
	void        Redo();
	void        Cut();
	void        Copy();
	void        VisGen();
	void        Paste();
	void        Delete();
	void        Duplicate();
	void        MoveUp();
	void        MoveDown();
	void        SelectAll();

	void        Matrix();

	void        TypeEdit();
	void        VariableEdit();

	void        ToggleGrid();
	void        ToggleMinSize();
	void        Settings();

	enum Code {
		A_LEFT, A_HCENTER, A_RIGHT, A_TOP, A_VCENTER, A_BOTTOM, A_LABEL,
		A_SAMEWIDTH, A_SAMEHEIGHT, A_SAMESIZE, A_VERTCENTER, A_HORZCENTER,
		A_MINWIDTH, A_MINHEIGHT, AUTOSPRING
	};

	void        Align(int type);
	void        SetSprings(dword s);
	void        ShowSelection(bool s);

	void        AddLayout();
	void        RenameLayout();
	void        RemoveLayout();
	void        PrevLayout();
	void        NextLayout();
	void        MoveLayoutUp();
	void        MoveLayoutDown();
	void        LayoutMenu(Bar& bar);

	void        EditBar(Bar& bar);
	void        AlignBar(Bar& bar);
	void        SizeBar(Bar& bar);
	void        MoveBar(Bar& bar);
	void        SpringBar(Bar& bar);
	void        OptionBar(Bar& bar);
	void        MainToolBar(Bar& bar);

	void        LayoutBar(Bar& bar);
	void        ItemBar(Bar& bar);
	void        MainMenuBar(Bar& bar);

	void        EditMenu(Bar& bar);

	void        SyncUsc();
	void        Save();
	void        CloseDesigner();

	void        SaveEditPos();
	void        RestoreEditPos();

	bool           Load(const char *filename, byte charset);

	typedef LayDes CLASSNAME;

	LayDes();

public:
	Ctrl&          DesignerCtrl()             { return km; }
	void           Serialize(Stream& s);
};

class LayDesigner : public IdeDesigner {
	LayDes         designer;
	ParentCtrl     parent;

public:
	virtual String GetFileName() const        { return designer.filename; }
	virtual void   Save()                     { designer.Save(); }
	virtual void   SyncUsc()                  { designer.SyncUsc(); }
	virtual void   SaveEditPos()              { designer.SaveEditPos(); }
	virtual void   EditMenu(Bar& menu)        { designer.EditMenu(menu); }
	virtual int    GetCharset() const         { return designer.charset; }
	virtual Ctrl&  DesignerCtrl()             { return parent; }

	void Serialize(Stream& s)                 { designer.Serialize(s); }
	bool Load(const char *filename, byte cs)  { return designer.Load(filename, cs); }

	LayDesigner()                             { parent.Add(designer.DesignerCtrl().SizePos()); }
};

#endif
