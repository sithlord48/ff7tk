/****************************************************************************/
//    copyright 2012 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7Item.h"
#include <QCoreApplication>

QString FF7Item::name(int i){return qApp->translate("Items",Items[i].name.toLocal8Bit());}
QString FF7Item::desc(int i){return qApp->translate("Item_desc",Items[i].desc.toLocal8Bit());}
int  FF7Item::type(int i){return Items[i].type;}
QString FF7Item::iconResource(int i){return Items[i].imageString.remove(":/");}
QImage FF7Item::image(int i){return QImage(Items[i].imageString);}
QIcon FF7Item::icon(int i){return QIcon(QPixmap::fromImage(image(i)));}
int FF7Item::materiaSlots(int i){return Items[i].mslots;}
int FF7Item::linkedSlots(int i){return Items[i].linked;}
int FF7Item::materiaGrowthRate(int i){return Items[i].mgrowth;}
int FF7Item::statHP(int i){return Items[i].hp;}
int FF7Item::statMP(int i){return Items[i].mp;}
int FF7Item::statSTR(int i){return Items[i].str;}
int FF7Item::statVIT(int i){return Items[i].vit;}
int FF7Item::statDEX(int i){return Items[i].dex;}
int FF7Item::statLCK(int i){return Items[i].lck;}
int FF7Item::statMAG(int i){return Items[i].mag;}
int FF7Item::statSPI(int i){return Items[i].spi;}
QString FF7Item::materiaSlotNoGrowthResource(void){return QString("items/m_no_grow_slot"); }
QString FF7Item::materiaSlotResource(void){return QString("items/m_grow_slot"); }
QString FF7Item::materiaLinkResource(void){return QString("items/mlink"); }
QImage FF7Item::imageMateriaSlotNoGrowth(void){return QImage(QString(":/items/m_no_grow_slot"));}
QImage FF7Item::imageMateriaSlot(void){return QImage(QString(":/items/m_grow_slot"));}
QImage FF7Item::imageMateriaLink(void){return QImage(QString(":/items/mlink"));}
int FF7Item::elementRestoration(int i){return Items[i].e_restoration;}
int FF7Item::elementFire(int i){return Items[i].e_fire;}
int FF7Item::elementCold(int i){return Items[i].e_cold;}
int FF7Item::elementLightning(int i){return Items[i].e_lightning;}
int FF7Item::elementEarth(int i){return Items[i].e_earth;}
int FF7Item::elementWind(int i){return Items[i].e_wind;}
int FF7Item::elementWater(int i){return Items[i].e_water;}
int FF7Item::elementGravity(int i){return Items[i].e_gravity;}
int FF7Item::elementHoly(int i){return Items[i].e_holy;}
int FF7Item::elementPoison(int i){return Items[i].e_poison;}
int FF7Item::elementCut(int i){return Items[i].e_cut;}
int FF7Item::elementShoot(int i){return Items[i].e_shoot;}
int FF7Item::elementPunch(int i){return Items[i].e_punch;}
int FF7Item::elementHit(int i){return Items[i].e_hit;}
//Status Functions
int FF7Item::statusDeath(int i){return Items[i].s_death;}
int FF7Item::statusSlowNumb(int i){return Items[i].s_slow_numb;}
int FF7Item::statusDeathSentence(int i){return Items[i].s_d_sentence;}
int FF7Item::statusParalysis(int i){return Items[i].s_paralysis;}
int FF7Item::statusPetrify(int i){return Items[i].s_petrify;}
int FF7Item::statusSilence(int i){return Items[i].s_silence;}
int FF7Item::statusSleep(int i){return Items[i].s_sleep;}
int FF7Item::statusConfusion(int i){return Items[i].s_confusion;}
int FF7Item::statusBerserk(int i){return Items[i].s_berserk;}
int FF7Item::statusFrog(int i){return Items[i].s_frog;}
int FF7Item::statusMini(int i){return Items[i].s_mini;}
int FF7Item::statusPoison(int i){return Items[i].s_poison;}
int FF7Item::statusFury(int i){return Items[i].s_fury;}
int FF7Item::statusSadness(int i){return Items[i].s_sadness;}
int FF7Item::statusDarkness(int i){return Items[i].s_darkness;}
int FF7Item::statusHaste(int i){return Items[i].s_haste;}
int FF7Item::statusSlow(int i){return Items[i].s_slow;}
int FF7Item::statusStop(int i){return Items[i].s_stop;}
int FF7Item::statusBarrier(int i){return Items[i].s_barrier;}
int FF7Item::statusMagicBarrier(int i){return Items[i].s_m_barrier;}
int FF7Item::statusReflect(int i){return Items[i].s_reflect;}
int FF7Item::statusShield(int i){return Items[i].s_sheild;}
int FF7Item::statusRegen(int i){return Items[i].s_regen;}
int FF7Item::statusResist(int i){return Items[i].s_resist;}
QString FF7Item::styleMateriaSlotNoGrowth(void)
{
	return QString("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.079096 rgba(77, 77, 77, 255), stop:0.152542 rgba(11, 28, 19, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
}
QString FF7Item::styleMateriaSlot(void)
{
	return QString("QPushButton:enabled{border: 0px;border-radius:16px;background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.814, fx:0.5, fy:0.5, stop:0 rgba(0, 1, 0, 255), stop:0.429379 rgba(37, 37, 37, 255), stop:0.514124 rgba(200, 195, 194, 255), stop:0.576271 rgba(153, 152, 152, 255), stop:0.655367 rgba(185, 181, 179, 255), stop:0.677966 rgba(37, 37, 37, 0));}QPushButton:hover{}");
}
QString FF7Item::styleMateriaLink(void)
{
	return QString("QLabel:enabled{background-color: qlineargradient(spread:reflect, x1:0.5, y1:0.5, x2:0.5, y2:0, stop:0.0225989 rgba(37, 37, 37, 255), stop:0.231638 rgba(153, 152, 152, 255), stop:0.389831 rgba(200, 195, 194, 255), stop:0.502825 rgba(138, 137, 137, 255), stop:0.621469 rgba(200, 195, 194, 255), stop:0.768362 rgba(138, 137, 137, 255), stop:0.932584 rgba(37, 37, 37, 0));}");
}

quint16 FF7Item::itemDecode( quint16 itemraw )
{//see FF7Save::itemDecode for full comments
	quint16 item;
	#ifdef Q_BYTE_ORDER
		#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
			item = itemraw;
		#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
			item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
		#else
			int one = 1;
			if (*(char *)&one){item = itemraw;}
			else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
		#endif
	#else
		int one = 1;
		if (*(char *)&one){item = itemraw;}
		else {item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);}
	#endif

	return item;
}
quint16 FF7Item::itemEncode( quint16 id, quint8 qty )
{//see FF7Save::itemEncode for full comments
	quint16 item,itemraw;
	#ifdef Q_BYTE_ORDER
		#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
			item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
			itemraw = item;
		#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
			item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
			itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
		#else
			int one = 1;
			if (*(char *)&one)
			{
				item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
				itemraw = item;
			}
			else
			{
				item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
				itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
			}
		#endif
	#else
		int one = 1;
		if (*(char *)&one)
		{
			item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
			itemraw = item;
		}
		else
		{
			item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
			itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
		}
	#endif

	return itemraw;
}

quint16 FF7Item::itemId(quint16 item)
{
	quint16 new_item = itemDecode(item);
	quint16 id = (new_item & 0x1FF);
	return id;
}
quint8 FF7Item::itemQty(quint16 item)
{
	quint16 new_item = itemDecode(item);
	quint8 qty;
	qty = (new_item & 0xFE00) >> 9;
	return qty;
}

QStringList FF7Item::elementalEffects(int id)
{
	QStringList elementList;
	if(id<0 || id>319){/*invalid number*/}
	else
	{
		for(int i=0;i<14;i++)
		{
			QString effect;
			int element=0;
			switch(i)
			{
				case 0: element=elementRestoration(id); effect.append(tr("Restoration"));break;
				case 1: element=elementFire(id); effect.append(tr("Fire")); break;
				case 2: element=elementCold(id); effect.append(tr("Cold")); break;
				case 3: element=elementLightning(id); effect.append(tr("Lightning")); break;
				case 4: element=elementEarth(id); effect.append(tr("Earth")); break;
				case 5: element=elementWind(id); effect.append(tr("Wind")); break;
				case 6: element=elementWater(id); effect.append(tr("Water")); break;
				case 7: element=elementGravity(id); effect.append(tr("Gravity")); break;
				case 8: element=elementHoly(id); effect.append(tr("Holy")); break;
				case 9: element=elementPoison(id); effect.append(tr("Poison")); break;
				case 10: element=elementCut(id); effect.append(tr("Cut")); break;
				case 11: element=elementShoot(id); effect.append(tr("Shoot")); break;
				case 12: element=elementPunch(id); effect.append(tr("Punch")); break;
				case 13: element=elementHit(id); effect.append(tr("Hit")); break;
			}
			switch(element)
			{
				case FF7Item::Absorb: effect.prepend(tr("Absorb:"));break;
				case FF7Item::Nullify: effect.prepend(tr("Nullify:"));break;
				case FF7Item::Halve: effect.prepend(tr("Halve:"));break;
				case FF7Item::NoEffect: effect.clear();break;
				case FF7Item::Damage: effect.prepend(tr("Attack:"));break;
			}
			if(!effect.isEmpty()) {
				elementList.append(effect);
			}
		}//end of for Loop
	}
	return elementList;
}

QStringList FF7Item::statusEffects(int id)
{
	QStringList statusList;
	if(id<0 || id>319){/*invalid number*/}
	else
	{
		for(int i=0;i<24;i++)
		{
			QString effect;
			int status=0;
			switch(i)
			{
				case 0: status=statusDeath(id); effect.append(tr("Death"));break;
				case 1: status=statusSlowNumb(id); effect.append(tr("Slow-Numb"));break;
				case 2: status=statusDeathSentence(id); effect.append(tr("D.Sentence"));break;
				case 3: status=statusParalysis(id); effect.append(tr("Paralysis"));break;
				case 4: status=statusPetrify(id); effect.append(tr("Petrify"));break;
				case 5: status=statusSilence(id); effect.append(tr("Silence"));break;
				case 6: status=statusSleep(id); effect.append(tr("Sleep"));break;
				case 7: status=statusConfusion(id); effect.append(tr("Confusion"));break;
				case 8: status=statusBerserk(id); effect.append(tr("Berserk"));break;
				case 9: status=statusFrog(id); effect.append(tr("Frog"));break;
				case 10: status=statusMini(id); effect.append(tr("Mini"));break;
				case 11: status=statusPoison(id); effect.append(tr("Poison"));break;
				case 12: status=statusFury(id); effect.append(tr("Fury"));break;
				case 13: status=statusSadness(id); effect.append(tr("Sadness"));break;
				case 14: status=statusDarkness(id); effect.append(tr("Darkness"));break;
				case 15: status=statusHaste(id); effect.append(tr("Haste"));break;
				case 16: status=statusSlow(id); effect.append(tr("Slow"));break;
				case 17: status=statusStop(id); effect.append(tr("Stop"));break;
				case 18: status=statusBarrier(id); effect.append(tr("Barrier"));break;
				case 19: status=statusMagicBarrier(id); effect.append(tr("M.Barrier"));break;
				case 20: status=statusReflect(id); effect.append(tr("Reflect"));break;
				case 21: status=statusShield(id); effect.append(tr("Shield"));break;
				case 22: status=statusRegen(id); effect.append(tr("Regen"));break;
				case 23:status=statusResist(id); effect.append(tr("Resist"));break;
			}
			switch(status)
			{
				case FF7Item::Protect: effect.prepend(tr("Protect:")); break;
				case FF7Item::Remove: effect.prepend(tr("Remove:")); break;
				case  FF7Item::NoEffect: effect.clear();break;
				case FF7Item::Infilict: effect.prepend(tr("Inflict:")); break;
				case FF7Item::SelfCast: effect.prepend(tr("OnBattle:"));break;
			}
			if(!effect.isEmpty()) {
				statusList.append(effect);
			}
		}//end of for Loop
	}
	return statusList;
}
