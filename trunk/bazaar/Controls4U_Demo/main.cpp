#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <Controls4U/Controls4U.h>

#if defined(PLATFORM_WIN32) 	
#include "Controls4U_Demo_win.h"
#endif
#include "JBControlsDemo.h"
#include "Controls4U_Demo.h"

#define IMAGEFILE <Controls4U_Demo/Controls4U_Demo.iml>
#define IMAGECLASS Images
#include <Draw/iml.h>

Controls4U_Demo::Controls4U_Demo() {
	CtrlLayout(*this, "Controls4U Demo");
	Sizeable().Zoomable();

	tab.Add(fileBrowser_Demo.SizePos(), "FileBrowser (experimental)");	
#if defined(PLATFORM_WIN32) 	
	tab.Add(vlc_Demo.SizePos(), "VLC ActiveX");
	tab.Add(firefox_Demo.SizePos(), "Firefox ActiveX");
	tab.Add(iexplorer_Demo.SizePos(), "Internet Explorer ActiveX");
#endif
	tab.Add(meter_Demo.SizePos(), "Meter & Knob");
	tab.Add(jbcontrols_Demo.SizePos(), "JBControls");
	tab.Add(staticClock_Demo.SizePos(), "StaticClock");
	tab.Add(editFileFolder_Demo.SizePos(), "StaticImage & EditFile/Folder");
	tab.Add(staticImageSet_Demo.SizePos(), "StaticImageSet");
	tab.Add(staticCtrls_Demo.SizePos(), "Static Controls");
	tab.Add(staticCtrlsTest_Demo.SizePos(), "Static Controls Test");
	//tab.Add(painterCanvas_Demo.SizePos(), "PainterCanvas (experimental)");
	tab.Add(functions4U_Demo.SizePos(), "Functions4U samples");

	tab.Set(tab.Find(jbcontrols_Demo));	// Select the last
	//tab.Set(tab.Find(painterCanvas_Demo));	// Select the last
	
	timerOn = false;
	SetTimeCallback(-100, THISBACK(Timer));
}

void Controls4U_Demo::Timer() {
	if (timerOn)
		return;
	timerOn = true;
	staticClock_Demo.UpdateInfo();
	timerOn = false;
#if defined(PLATFORM_WIN32)
	firefox_Demo.UpdateInfo();
	iexplorer_Demo.UpdateInfo();
	vlc_Demo.UpdateInfo();
#endif	
}

GUI_APP_MAIN {
	Controls4U_Demo().Run();
}

EditFileFolder_Demo::EditFileFolder_Demo() {
	CtrlLayout(*this);

	FileName.ActiveDir(GetDesktopFolder());
	FileName.Type("Image files", "*.png, *.jpg, *.jpeg, *.tif*, *.bmp, *.gif");
	FileName.AllFilesType();
	FileName.WhenChange = THISBACK(OnNewFile);
	angleList.Add(0, "0º").Add(1, "90º").Add(2, "180º").Add(3, "270º").SetData(0);
	angleList.WhenAction = THISBACK(ChangeProperties);
	imageFit.Add(0, "BestFit").Add(1, "FillFrame").Add(2, "NoScale").Add(3, "RepeatToFill").SetData(0);
	imageFit.WhenAction = THISBACK(ChangeProperties);
	
	back.Set(Images::paper());
}
void EditFileFolder_Demo::OnNewFile() {
	if (!clipImage.Set(~FileName))
		Exclamation("File not found");
}
void EditFileFolder_Demo::ChangeProperties() {
	clipImage.SetAngle(~angleList);
	clipImage.SetFit(~imageFit);
}

StaticCtrls_Demo::StaticCtrls_Demo() {
	CtrlLayout(*this);
	
	back.Set(Images::paper());
}

StaticCtrlsTest_Demo::StaticCtrlsTest_Demo() {
	CtrlLayout(*this);
}

void StaticClock_Demo::UpdateInfo() {	
	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext()) {
		if (StaticClock *c = dynamic_cast<StaticClock *>(q))
			if (!c->IsAuto())
				c->SetTime();
	}
}
void StaticClock_Demo::ChangeProperties() {
	clock10.SetHourType(~hourType);
	clock10.SetNumberType(~numberType);
	clock10.SetColorType(~colorType);
	clock10.Seconds(checkSeconds);
	if (checkImage)
		clock10.SetImage(Images::ClockImage());
	else
		clock10.SetImage((Image)Null);
}

StaticClock_Demo::StaticClock_Demo() {
	CtrlLayout(*this);
	clock9.SetImage(Images::ClockImage());
	hourType.Add(0, "No").Add(1, "Square").Add(2, "Rectangle").SetData(2);
	hourType.WhenAction = THISBACK(ChangeProperties);
	numberType.Add(0, "NoNumber").Add(1, "Small").Add(2, "Big").Add(3, "BigSmall").Add(4, "Big4").SetData(0);
	numberType.WhenAction = THISBACK(ChangeProperties);
	colorType.Add(0, "WhiteType").Add(1, "BlackType").SetData(1);
	colorType.WhenAction = THISBACK(ChangeProperties);
	checkSeconds = true;
	checkSeconds.WhenAction = THISBACK(ChangeProperties);
	checkImage = false;
	checkImage.WhenAction = THISBACK(ChangeProperties);
	back.Set(Images::cream2());
};

void Meter_Demo::ChangeValueKnob(Knob *knob, Meter *meter) {
	*meter <<= ~*knob;
}

void Meter_Demo::ChangeProperties() {
	meter1.SetColorType(~colorType);
	meter1.SetNumber(checkNumber);
}

void Meter_Demo::ChangePropertiesKnob() {
	knob1.SetColorType(~knobColorType);
	knob1.SetNumber(knobCheckNumber);
	knob1.SetInterlocking(knobCheckInterlocking);
	knob1.SetMark(~knobSetMark);
	knob1.ClockWise(~knobCheckClockWise);
	knob1.SetStyle(~knobSetStyle);
}

Meter_Demo::Meter_Demo() {
	CtrlLayout(*this);
	knob1.WhenSlideFinish = THISBACK2(ChangeValueKnob, &knob1, &meter1);
	knob2.WhenSlideFinish = THISBACK2(ChangeValueKnob, &knob2, &meter2);
	knob3.WhenSlideFinish = THISBACK2(ChangeValueKnob, &knob3, &meter3);
	knob4.WhenSlideFinish = THISBACK2(ChangeValueKnob, &knob4, &meter4);
	knob5.WhenSlideFinish = THISBACK2(ChangeValueKnob, &knob5, &meter5);	
	colorType.Add(Meter::WhiteType, "WhiteType").Add(Meter::BlackType, "BlackType")
			 .SetData(Meter::BlackType);
	colorType.WhenAction = THISBACK(ChangeProperties);	
	checkNumber.WhenAction = THISBACK(ChangeProperties);
	checkNumber = true;
	knobColorType.Add(Knob::SimpleWhiteType, "SimpleWhiteType")
				 .Add(Knob::SimpleBlackType, "SimpleBlackType")
				 .Add(Knob::WhiteType, "WhiteType")
				 .Add(Knob::BlackType, "BlackType").SetData(Knob::BlackType);
	knobColorType.WhenAction = THISBACK(ChangePropertiesKnob);	
	knobCheckNumber = true;
	knobCheckNumber.WhenAction = THISBACK(ChangePropertiesKnob);	
	knobCheckInterlocking.WhenAction = THISBACK(ChangePropertiesKnob);	
	knobCheckClockWise = true;
	knobCheckClockWise.WhenAction = THISBACK(ChangePropertiesKnob);	
	knobSetMark.Add(Knob::NoMark, "NoMark")
			   .Add(Knob::Line, "Line")
			   .Add(Knob::Circle, "Circle").SetData(Knob::Circle);
	knobSetMark.WhenAction = THISBACK(ChangePropertiesKnob);	
	knobSetStyle.Add(Knob::Simple, "Simple")
			    .Add(Knob::Rugged, "Rugged").SetData(Knob::Simple);
	knobSetStyle.WhenAction = THISBACK(ChangePropertiesKnob);	
	back.Set(Images::cream2());
}

FileBrowser_Demo::FileBrowser_Demo() {
	CtrlLayout(*this);

	browser.SetReadOnly().SetUseTrashBin().SetBrowseLinks().SetDeleteReadOnly()./*SetAskBeforeDelete().*/SetDragAndDrop();
	
	browser.WhenAction = THISBACK(FileOpened);
	browser.WhenSelected = THISBACK(FileSelected);
	back.Set(Images::paper());
}

void FileBrowser_Demo::FileSelected() {
	fileSelected = ~browser;
}

void FileBrowser_Demo::FileOpened() {
	if (!LaunchFile(~browser))
		Exclamation(Format(t_("Sorry. It is not possible to open %s"), DeQtf(~browser)));
}

void FileBrowser_Demo::ChangeProperties() {
}

Functions4U_Demo::Functions4U_Demo() {
	CtrlLayout(*this);
	
	String myqtf;

	QtfRichObject a = QtfEquation("-sqrt(2/3)");
	QtfRichObject b = QtfEquation("integral(-sqrt(cos(phi_ini^2)) + i^2 + 6, i = 1, 10)*dx = cos((27+x^2)^3.25)/(PI*R_0^2)");
	QtfRichObject c = QtfEquation("delta_i = a+b*x+c*x^2+d*x^3");
	QtfRichObject d = QtfEquation("sqrt(cos(p^2))");
	QtfRichObject e = QtfEquation("summation(a+b*x+c*x^2+d*x^3, x = h, h+1)*dx = SI_h");
	QtfRichObject f = QtfEquation("exp(-1/2*(b-r)/a*t)*r*a*(d*b*w^2*a+d*r*w^2*a-d*r*c+d*b*c+2*f1*w*a*c)/((2*w^2*a)^2+b^2-2*c*a-b*r)");
	
	myqtf << "[R3 This are some formulas in QTF:&" << a << "&" << b << "&" << c << "&" << d << "&" << e << "&" << f;

	equation.SetData(myqtf);

	butDiff.WhenAction = THISBACK(OnDiff);	
	butPatch.WhenAction = THISBACK(OnPatch);
	butShowEquation.WhenAction = THISBACK(OnSet);
}

void Functions4U_Demo::OnDiff() {
	if (!BSDiff(~editOriginal, ~editNew, ~editPatch)) 
		Exclamation(DeQtf(BsGetLastError()));
}

void Functions4U_Demo::OnPatch() {
	if (!BSPatch(~editOriginal, ~editNew, ~editPatch)) 
		Exclamation(DeQtf(BsGetLastError()));
}

void Functions4U_Demo::OnSet() {
	String myqtf;

	QtfRichObject a = QtfEquation(strEquation);
	
	myqtf << a;

	userEquation.SetData(myqtf);	
}
	
PainterCanvas_Demo::PainterCanvas_Demo() {
	CtrlLayout(*this);

	//imgCtrl.SetImage(Images::ClockImage());
	//LoadSvg(drawingCanvas, AppendFileName(GetDesktopFolder(), "svg/demo.svg"));
	
	LineElem &elem = static_cast<LineElem&>(painterCanvas.elemList.elems.Add(new LineElem(100, 100, 200, 200)));
	elem.style.SetStrokeColor(Green()).SetStrokeWidth(3);
}

StaticImageSet_Demo::StaticImageSet_Demo() {
	CtrlLayout(*this);

	imageSet.Add(Images::cream2());
	imageSet.Add(Images::paper());
	imageSet.Add(Images::ClockImage());
}
