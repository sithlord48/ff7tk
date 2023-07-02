/****************************************************************************/
//    copyright 2021  Chris Rizzitello <sithlord48@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include <QObject>

#include "../../src/data/FF7Text.h"

class FF7Text_Test : public QObject
{
    Q_OBJECT
private slots:
    void test_toPCENG();
    void test_toFF7ENG();
    void test_setJapanese();
    void test_toPCJPN();
    void test_toFF7JPN();

private:
    const QByteArray range0x = QByteArray::fromRawData("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F", 16);
    const QByteArray range1x = QByteArray::fromRawData("\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 16);
    const QByteArray range2x = QByteArray::fromRawData("\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F", 16);
    const QByteArray range3x = QByteArray::fromRawData("\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F", 16);
    const QByteArray range4x = QByteArray::fromRawData("\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F", 16);
    const QByteArray range5x = QByteArray::fromRawData("\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F", 16);
    const QByteArray range6x = QByteArray::fromRawData("\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F", 16);
    const QByteArray range7x = QByteArray::fromRawData("\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F", 16);
    const QByteArray range8x = QByteArray::fromRawData("\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F", 16);
    const QByteArray range9x = QByteArray::fromRawData("\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F", 16);
    const QByteArray rangeAx = QByteArray::fromRawData("\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF", 16);
    const QByteArray rangeBx = QByteArray::fromRawData("\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF", 16);
    const QByteArray rangeCx = QByteArray::fromRawData("\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF", 16);
    const QByteArray rangeDx = QByteArray::fromRawData("\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF", 16);
    const QByteArray rangeEx = QByteArray::fromRawData("\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF", 16);
    const QByteArray rangeFx = QByteArray::fromRawData("\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9", 10);

    const QString range0xE = QStringLiteral(" !\"#$%&\'()*+,-./");
    const QString range1xE = QStringLiteral("0123456789:;<=>?");
    const QString range2xE = QStringLiteral("@ABCDEFGHIJKLMNO");
    const QString range3xE = QStringLiteral("PQRSTUVWXYZ[\\]^_");
    const QString range4xE = QStringLiteral("`abcdefghijklmno");
    const QString range5xE = QStringLiteral("pqrstuvwxyz{|}~");
    const QString range6xE = QStringLiteral("ÄÅÇÉÑÖÜáàâäãåçéè");
    const QString range7xE = QStringLiteral("êëíìîïñóòôöõúùûü");
    const QString range8xE = QStringLiteral("⌘°¢£ÙÛ¶ß®©™´¨≠ÆØ");
    const QString range9xE = QStringLiteral("∞±≤≥¥µ∂ΣΠπ⌡ªºΩæø");
    const QString rangeAxE = QStringLiteral("¿¡¬√ƒ≈∆«»…ÀÃÕŒœ");
    const QString rangeBxE = QStringLiteral("–—“”‘’÷◊ÿŸ⁄¤‹›ﬁﬂ");
    const QString rangeCxE = QStringLiteral("■▪‚„‰ÂÊÁËÈÍÎÏÌÓÔ");
    const QString rangeDxE = QStringLiteral("ÒÙÛ");
    const QString rangeExE = QStringLiteral("{CHOICE}\t, .\"…\"\n\n{NEW PAGE}\n\n{NEW PAGE 2}\n{CLOUD}{BARRET}{TIFA}{AERITH}{RED XIII}{YUFFIE}");
    const QString rangeFxE = QStringLiteral("{CAIT SITH}{VINCENT}{CID}{MEMBER 1}{MEMBER 2}{MEMBER 3}{CIRCLE}{TRIANGLE}{SQUARE}{CROSS}");
    const QString rangeFEDxE = QStringLiteral("{GREY}{BLUE}{RED}{PURPLE}{GREEN}{CYAN}{YELLOW}{WHITE}{BLINK}{MULTICOLOUR}{PAUSE}{PAUSE066}{VARDEC}{VARHEX}");
    const QString rangeFEExE = QStringLiteral("{SCROLLING}{VARDECR}{MEMORY:var[11][1];size=3}{SPACED CHARACTERS}");

    const QString range0xJ = QStringLiteral("バばビびブぶベべボぼガがギぎグぐ");
    const QString range1xJ = QStringLiteral("ゲげゴごザざジじズずゼぜゾぞダだ");
    const QString range2xJ = QStringLiteral("ヂぢヅづデでドどヴパぱピぴプぷペ");
    const QString range3xJ = QStringLiteral("ぺポぽ０１２３４５６７８９、。　");
    const QString range4xJ = QStringLiteral("ハはヒひフふヘへホほカかキきクく");
    const QString range5xJ = QStringLiteral("ケけコこサさシしスすセせソそタた");
    const QString range6xJ = QStringLiteral("チちツつテてトとウうアあイいエえ");
    const QString range7xJ = QStringLiteral("オおナなニにヌぬネねノのマまミみ");
    const QString range8xJ = QStringLiteral("ムむメめモもラらリりルるレれロろ");
    const QString range9xJ = QStringLiteral("ヤやユゆヨよワわンんヲをッっャゃ");
    const QString rangeAxJ = QStringLiteral("ュゅョょァぁィぃゥぅェぇォぉ！？");
    const QString rangeBxJ = QStringLiteral("『』．＋ＡＢＣＤＥＦＧＨＩＪＫＬ");
    const QString rangeCxJ = QStringLiteral("ＭＮＯＰＱＲＳＴＵＶＷＸＹＺ・＊");
    const QString rangeDxJ = QStringLiteral("ー～…％／：＆【】♥→αβ「」（");
    const QString rangeExJ = QStringLiteral("）－＝⑬\n\n{NEW PAGE}\n\n{NEW PAGE 2}\n{CLOUD}{BARRET}{TIFA}{AERITH}{RED XIII}{YUFFIE}");
    const QString rangeFxJ = QStringLiteral("{CAIT SITH}{VINCENT}{CID}{MEMBER 1}{MEMBER 2}{MEMBER 3}{CIRCLE}{TRIANGLE}{SQUARE}{CROSS}");

    const QByteArray rangeFA0x = QByteArray::fromRawData("\xFA\x00\xFA\x01\xFA\x02\xFA\x03\xFA\x04\xFA\x05\xFA\x06\xFA\x07\xFA\x08\xFA\x09\xFA\x0A\xFA\x0B\xFA\x0C\xFA\x0D\xFA\x0E\xFA\x0F", 32);
    const QByteArray rangeFA1x = QByteArray::fromRawData("\xFA\x10\xFA\x11\xFA\x12\xFA\x13\xFA\x14\xFA\x15\xFA\x16\xFA\x17\xFA\x18\xFA\x19\xFA\x1A\xFA\x1B\xFA\x1C\xFA\x1D\xFA\x1E\xFA\x1F", 32);
    const QByteArray rangeFA2x = QByteArray::fromRawData("\xFA\x20\xFA\x21\xFA\x22\xFA\x23\xFA\x24\xFA\x25\xFA\x26\xFA\x27\xFA\x28\xFA\x29\xFA\x2A\xFA\x2B\xFA\x2C\xFA\x2D\xFA\x2E\xFA\x2F", 32);
    const QByteArray rangeFA3x = QByteArray::fromRawData("\xFA\x30\xFA\x31\xFA\x32\xFA\x33\xFA\x34\xFA\x35\xFA\x36\xFA\x37\xFA\x38\xFA\x39\xFA\x3A\xFA\x3B\xFA\x3C\xFA\x3D\xFA\x3E\xFA\x3F", 32);
    const QByteArray rangeFA4x = QByteArray::fromRawData("\xFA\x40\xFA\x41\xFA\x42\xFA\x43\xFA\x44\xFA\x45\xFA\x46\xFA\x47\xFA\x48\xFA\x49\xFA\x4A\xFA\x4B\xFA\x4C\xFA\x4D\xFA\x4E\xFA\x4F", 32);
    const QByteArray rangeFA5x = QByteArray::fromRawData("\xFA\x50\xFA\x51\xFA\x52\xFA\x53\xFA\x54\xFA\x55\xFA\x56\xFA\x57\xFA\x58\xFA\x59\xFA\x5A\xFA\x5B\xFA\x5C\xFA\x5D\xFA\x5E\xFA\x5F", 32);
    const QByteArray rangeFA6x = QByteArray::fromRawData("\xFA\x60\xFA\x61\xFA\x62\xFA\x63\xFA\x64\xFA\x65\xFA\x66\xFA\x67\xFA\x68\xFA\x69\xFA\x6A\xFA\x6B\xFA\x6C\xFA\x6D\xFA\x6E\xFA\x6F", 32);
    const QByteArray rangeFA7x = QByteArray::fromRawData("\xFA\x70\xFA\x71\xFA\x72\xFA\x73\xFA\x74\xFA\x75\xFA\x76\xFA\x77\xFA\x78\xFA\x79\xFA\x7A\xFA\x7B\xFA\x7C\xFA\x7D\xFA\x7E\xFA\x7F", 32);
    const QByteArray rangeFA8x = QByteArray::fromRawData("\xFA\x80\xFA\x81\xFA\x82\xFA\x83\xFA\x84\xFA\x85\xFA\x86\xFA\x87\xFA\x88\xFA\x89\xFA\x8A\xFA\x8B\xFA\x8C\xFA\x8D\xFA\x8E\xFA\x8F", 32);
    const QByteArray rangeFA9x = QByteArray::fromRawData("\xFA\x90\xFA\x91\xFA\x92\xFA\x93\xFA\x94\xFA\x95\xFA\x96\xFA\x97\xFA\x98\xFA\x99\xFA\x9A\xFA\x9B\xFA\x9C\xFA\x9D\xFA\x9E\xFA\x9F", 32);
    const QByteArray rangeFAAx = QByteArray::fromRawData("\xFA\xA0\xFA\xA1\xFA\xA2\xFA\xA3\xFA\xA4\xFA\xA5\xFA\xA6\xFA\xA7\xFA\xA8\xFA\xA9\xFA\xAA\xFA\xAB\xFA\xAC\xFA\xAD\xFA\xAE\xFA\xAF", 32);
    const QByteArray rangeFABx = QByteArray::fromRawData("\xFA\xB0\xFA\xB1\xFA\xB2\xFA\xB3\xFA\xB4\xFA\xB5\xFA\xB6\xFA\xB7\xFA\xB8\xFA\xB9\xFA\xBA\xFA\xBB\xFA\xBC\xFA\xBD\xFA\xBE\xFA\xBF", 32);
    const QByteArray rangeFACx = QByteArray::fromRawData("\xFA\xC0\xFA\xC1\xFA\xC2\xFA\xC3\xFA\xC4\xFA\xC5\xFA\xC6\xFA\xC7\xFA\xC8\xFA\xC9\xFA\xCA\xFA\xCB\xFA\xCC\xFA\xCD\xFA\xCE\xFA\xCF", 32);
    const QByteArray rangeFADx = QByteArray::fromRawData("\xFA\xD0\xFA\xD1", 4);

    const QString rangeFA0xJ = QStringLiteral("必殺技地獄火炎裁雷大怒斬鉄剣槍海");
    const QString rangeFA1xJ = QStringLiteral("衝聖審判転生改暗黒釜天崩壊零式自");
    const QString rangeFA2xJ = QStringLiteral("爆使放射臭息死宣告凶破晄撃画龍晴");
    const QString rangeFA3xJ = QStringLiteral("点睛超究武神覇癒風邪気封印吹烙星");
    const QString rangeFA4xJ = QStringLiteral("守護命鼓動福音掌打水面蹴乱闘合体");
    const QString rangeFA5xJ = QStringLiteral("疾迅明鏡止抜山蓋世血祭鎧袖一触者");
    const QString rangeFA6xJ = QStringLiteral("滅森羅万象装備器攻魔法召喚獣呼出");
    const QString rangeFA7xJ = QStringLiteral("持相手物確率弱投付与変化片方行決");
    const QString rangeFA8xJ = QStringLiteral("定分直前真似覚列後位置防御発回連");
    const QString rangeFA9xJ = QStringLiteral("続敵全即効果尾毒消金針乙女興奮剤");
    const QString rangeFAAxJ = QStringLiteral("鎮静能薬英雄榴弾右腕砂時計糸戦惑");
    const QString rangeFABxJ = QStringLiteral("草牙南極冷結晶電鳥角有害質爪光月");
    const QString rangeFACxJ = QStringLiteral("反巨目砲重力球空双野菜実兵単毛茶");
    const QString rangeFADxJ = QStringLiteral("色髪");

    const QByteArray rangeFB0x = QByteArray::fromRawData("\xFB\x00\xFB\x01\xFB\x02\xFB\x03\xFB\x04\xFB\x05\xFB\x06\xFB\x07\xFB\x08\xFB\x09\xFB\x0A\xFB\x0B\xFB\x0C\xFB\x0D\xFB\x0E\xFB\x0F", 32);
    const QByteArray rangeFB1x = QByteArray::fromRawData("\xFB\x10\xFB\x11\xFB\x12\xFB\x13\xFB\x14\xFB\x15\xFB\x16\xFB\x17\xFB\x18\xFB\x19\xFB\x1A\xFB\x1B\xFB\x1C\xFB\x1D\xFB\x1E\xFB\x1F", 32);
    const QByteArray rangeFB2x = QByteArray::fromRawData("\xFB\x20\xFB\x21\xFB\x22\xFB\x23\xFB\x24\xFB\x25\xFB\x26\xFB\x27\xFB\x28\xFB\x29\xFB\x2A\xFB\x2B\xFB\x2C\xFB\x2D\xFB\x2E\xFB\x2F", 32);
    const QByteArray rangeFB3x = QByteArray::fromRawData("\xFB\x30\xFB\x31\xFB\x32\xFB\x33\xFB\x34\xFB\x35\xFB\x36\xFB\x37\xFB\x38\xFB\x39\xFB\x3A\xFB\x3B\xFB\x3C\xFB\x3D\xFB\x3E\xFB\x3F", 32);
    const QByteArray rangeFB4x = QByteArray::fromRawData("\xFB\x40\xFB\x41\xFB\x42\xFB\x43\xFB\x44\xFB\x45\xFB\x46\xFB\x47\xFB\x48\xFB\x49\xFB\x4A\xFB\x4B\xFB\x4C\xFB\x4D\xFB\x4E\xFB\x4F", 32);
    const QByteArray rangeFB5x = QByteArray::fromRawData("\xFB\x50\xFB\x51\xFB\x52\xFB\x53\xFB\x54\xFB\x55\xFB\x56\xFB\x57\xFB\x58\xFB\x59\xFB\x5A\xFB\x5B\xFB\x5C\xFB\x5D\xFB\x5E\xFB\x5F", 32);
    const QByteArray rangeFB6x = QByteArray::fromRawData("\xFB\x60\xFB\x61\xFB\x62\xFB\x63\xFB\x64\xFB\x65\xFB\x66\xFB\x67\xFB\x68\xFB\x69\xFB\x6A\xFB\x6B\xFB\x6C\xFB\x6D\xFB\x6E\xFB\x6F", 32);
    const QByteArray rangeFB7x = QByteArray::fromRawData("\xFB\x70\xFB\x71\xFB\x72\xFB\x73\xFB\x74\xFB\x75\xFB\x76\xFB\x77\xFB\x78\xFB\x79\xFB\x7A\xFB\x7B\xFB\x7C\xFB\x7D\xFB\x7E\xFB\x7F", 32);
    const QByteArray rangeFB8x = QByteArray::fromRawData("\xFB\x80\xFB\x81\xFB\x82\xFB\x83\xFB\x84\xFB\x85\xFB\x86\xFB\x87\xFB\x88\xFB\x89\xFB\x8A\xFB\x8B\xFB\x8C\xFB\x8D\xFB\x8E\xFB\x8F", 32);
    const QByteArray rangeFB9x = QByteArray::fromRawData("\xFB\x90\xFB\x91\xFB\x92\xFB\x93\xFB\x94\xFB\x95\xFB\x96\xFB\x97\xFB\x98\xFB\x99\xFB\x9A\xFB\x9B\xFB\x9C\xFB\x9D\xFB\x9E\xFB\x9F", 32);
    const QByteArray rangeFBAx = QByteArray::fromRawData("\xFB\xA0\xFB\xA1\xFB\xA2\xFB\xA3\xFB\xA4\xFB\xA5\xFB\xA6\xFB\xA7\xFB\xA8\xFB\xA9\xFB\xAA\xFB\xAB\xFB\xAC\xFB\xAD\xFB\xAE\xFB\xAF", 32);
    const QByteArray rangeFBBx = QByteArray::fromRawData("\xFB\xB0\xFB\xB1\xFB\xB2\xFB\xB3\xFB\xB4\xFB\xB5\xFB\xB6\xFB\xB7\xFB\xB8\xFB\xB9\xFB\xBA\xFB\xBB\xFB\xBC\xFB\xBD\xFB\xBE\xFB\xBF", 32);
    const QByteArray rangeFBCx = QByteArray::fromRawData("\xFB\xC0\xFB\xC1\xFB\xC2\xFB\xC3\xFB\xC4\xFB\xC5\xFB\xC6\xFB\xC7\xFB\xC8\xFB\xC9\xFB\xCA\xFB\xCB\xFB\xCC\xFB\xCD\xFB\xCE\xFB\xCF", 32);
    const QByteArray rangeFBDx = QByteArray::fromRawData("\xFB\xD0\xFB\xD1\xFB\xD2\xFB\xD3\xFB\xD4\xFB\xD5\xFB\xD6\xFB\xD7\xFB\xD8\xFB\xD9\xFB\xDA\xFB\xDB\xFB\xDC\xFB\xDD\xFB\xDE\xFB\xDF", 32);
    const QByteArray rangeFBEx = QByteArray::fromRawData("\xFB\xE0\xFB\xE1\xFB\xE2\xFB\xE3\xFB\xE4\xFB\xE5\xFB\xE6", 14);

    const QString rangeFB0xJ = QStringLiteral("安香花会員蜂蜜館下着入先不子供屋");
    const QString rangeFB1xJ = QStringLiteral("商品景交換階模型部離場所仲間無制");
    const QString rangeFB2xJ = QStringLiteral("限殿様秘氷河図何材料雪上進事古代");
    const QString rangeFB3xJ = QStringLiteral("種鍵娘紙町住奥眠楽最初村雨釘陸吉");
    const QString rangeFB4xJ = QStringLiteral("揮叢雲軍異常通威父蛇矛青偃刀戟十");
    const QString rangeFB5xJ = QStringLiteral("字裏車円輪卍折鶴倶戴螺貝突銀玉正");
    const QString rangeFB6xJ = QStringLiteral("宗具甲烈属性吸収半減土高級状態縁");
    const QString rangeFB7xJ = QStringLiteral("闇睡石徐々的指混呪開始歩復盗小治");
    const QString rangeFB8xJ = QStringLiteral("理同速遅逃去視複味沈黙還倍数瀕取");
    const QString rangeFB9xJ = QStringLiteral("返人今差誰当拡散飛以外暴避振身中");
    const QString rangeFBAxJ = QStringLiteral("旋津波育機械擲炉新両本君洞内作警");
    const QString rangeFBBxJ = QStringLiteral("特殊板強穴隊族亡霊鎖足刃頭怪奇虫");
    const QString rangeFBCxJ = QStringLiteral("跳侍左首潜長親衛塔宝条像忍謎般見");
    const QString rangeFBDxJ = QStringLiteral("報充填完了銃元経験値終獲得名悲蛙");
    const QString rangeFBExJ = QStringLiteral("操成費背切替割");

    const QByteArray rangeFC0x = QByteArray::fromRawData("\xFC\x00\xFC\x01\xFC\x02\xFC\x03\xFC\x04\xFC\x05\xFC\x06\xFC\x07\xFC\x08\xFC\x09\xFC\x0A\xFC\x0B\xFC\x0C\xFC\x0D\xFC\x0E\xFC\x0F", 32);
    const QByteArray rangeFC1x = QByteArray::fromRawData("\xFC\x10\xFC\x11\xFC\x12\xFC\x13\xFC\x14\xFC\x15\xFC\x16\xFC\x17\xFC\x18\xFC\x19\xFC\x1A\xFC\x1B\xFC\x1C\xFC\x1D\xFC\x1E\xFC\x1F", 32);
    const QByteArray rangeFC2x = QByteArray::fromRawData("\xFC\x20\xFC\x21\xFC\x22\xFC\x23\xFC\x24\xFC\x25\xFC\x26\xFC\x27\xFC\x28\xFC\x29\xFC\x2A\xFC\x2B\xFC\x2C\xFC\x2D\xFC\x2E\xFC\x2F", 32);
    const QByteArray rangeFC3x = QByteArray::fromRawData("\xFC\x30\xFC\x31\xFC\x32\xFC\x33\xFC\x34\xFC\x35\xFC\x36\xFC\x37\xFC\x38\xFC\x39\xFC\x3A\xFC\x3B\xFC\x3C\xFC\x3D\xFC\x3E\xFC\x3F", 32);
    const QByteArray rangeFC4x = QByteArray::fromRawData("\xFC\x40\xFC\x41\xFC\x42\xFC\x43\xFC\x44\xFC\x45\xFC\x46\xFC\x47\xFC\x48\xFC\x49\xFC\x4A\xFC\x4B\xFC\x4C\xFC\x4D\xFC\x4E\xFC\x4F", 32);
    const QByteArray rangeFC5x = QByteArray::fromRawData("\xFC\x50\xFC\x51\xFC\x52\xFC\x53\xFC\x54\xFC\x55\xFC\x56\xFC\x57\xFC\x58\xFC\x59\xFC\x5A\xFC\x5B\xFC\x5C\xFC\x5D\xFC\x5E\xFC\x5F", 32);
    const QByteArray rangeFC6x = QByteArray::fromRawData("\xFC\x60\xFC\x61\xFC\x62\xFC\x63\xFC\x64\xFC\x65\xFC\x66\xFC\x67\xFC\x68\xFC\x69\xFC\x6A\xFC\x6B\xFC\x6C\xFC\x6D\xFC\x6E\xFC\x6F", 32);
    const QByteArray rangeFC7x = QByteArray::fromRawData("\xFC\x70\xFC\x71\xFC\x72\xFC\x73\xFC\x74\xFC\x75\xFC\x76\xFC\x77\xFC\x78\xFC\x79\xFC\x7A\xFC\x7B\xFC\x7C\xFC\x7D\xFC\x7E\xFC\x7F", 32);
    const QByteArray rangeFC8x = QByteArray::fromRawData("\xFC\x80\xFC\x81\xFC\x82\xFC\x83\xFC\x84\xFC\x85\xFC\x86\xFC\x87\xFC\x88\xFC\x89\xFC\x8A\xFC\x8B\xFC\x8C\xFC\x8D\xFC\x8E\xFC\x8F", 32);
    const QByteArray rangeFC9x = QByteArray::fromRawData("\xFC\x90\xFC\x91\xFC\x92\xFC\x93\xFC\x94\xFC\x95\xFC\x96\xFC\x97\xFC\x98\xFC\x99\xFC\x9A\xFC\x9B\xFC\x9C\xFC\x9D\xFC\x9E\xFC\x9F", 32);
    const QByteArray rangeFCAx = QByteArray::fromRawData("\xFC\xA0\xFC\xA1\xFC\xA2\xFC\xA3\xFC\xA4\xFC\xA5\xFC\xA6\xFC\xA7\xFC\xA8\xFC\xA9\xFC\xAA\xFC\xAB\xFC\xAC\xFC\xAD\xFC\xAE\xFC\xAF", 32);
    const QByteArray rangeFCBx = QByteArray::fromRawData("\xFC\xB0\xFC\xB1\xFC\xB2\xFC\xB3\xFC\xB4\xFC\xB5\xFC\xB6\xFC\xB7\xFC\xB8\xFC\xB9\xFC\xBA\xFC\xBB\xFC\xBC\xFC\xBD\xFC\xBE\xFC\xBF", 32);
    const QByteArray rangeFCCx = QByteArray::fromRawData("\xFC\xC0\xFC\xC1\xFC\xC2\xFC\xC3\xFC\xC4\xFC\xC5\xFC\xC6\xFC\xC7\xFC\xC8\xFC\xC9\xFC\xCA\xFC\xCB\xFC\xCC\xFC\xCD\xFC\xCE\xFC\xCF", 32);
    const QByteArray rangeFCDx = QByteArray::fromRawData("\xFC\xD0\xFC\xD1", 4);

    const QString rangeFC0xJ = QStringLiteral("由閉記憶選番街底忘都過艇路運搬船");
    const QString rangeFC1xJ = QStringLiteral("墓心港末宿西道艦家乗竜巻迷宮絶壁");
    const QString rangeFC2xJ = QStringLiteral("支社久件想秒予多落受組余系標起迫");
    const QString rangeFC3xJ = QStringLiteral("日勝形引現解除磁互口廃棄汚染液活");
    const QString rangeFC4xJ = QStringLiteral("令副隠主斉登温泉百段熱走急降奪響");
    const QString rangeFC5xJ = QStringLiteral("嵐移危戻遠吠軟骨言葉震叫噴舞狩粉");
    const QString rangeFC6xJ = QStringLiteral("失敗眼激盤逆鱗踏喰盾叩食凍退木吐");
    const QString rangeFC7xJ = QStringLiteral("線魅押潰曲翼教皇太陽界案挑援赤往");
    const QString rangeFC8xJ = QStringLiteral("殴意東北参知聞来仕別集信用思毎悪");
    const QString rangeFC9xJ = QStringLiteral("枯考然張好伍早各独配腐話帰永救感");
    const QString rangeFCAxJ = QStringLiteral("故売浮市加流約宇礼束母男年待宙立");
    const QString rangeFCBxJ = QStringLiteral("残俺少精士私険関倒休我許郷助要問");
    const QString rangeFCCxJ = QStringLiteral("係旧固荒稼良議導夢追説声任柱満未");
    const QString rangeFCDxJ = QStringLiteral("顔旅");

    const QByteArray rangeFD0x = QByteArray::fromRawData("\xFD\x00\xFD\x01\xFD\x02\xFD\x03\xFD\x04\xFD\x05\xFD\x06\xFD\x07\xFD\x08\xFD\x09\xFD\x0A\xFD\x0B\xFD\x0C\xFD\x0D\xFD\x0E\xFD\x0F", 32);
    const QByteArray rangeFD1x = QByteArray::fromRawData("\xFD\x10\xFD\x11\xFD\x12\xFD\x13\xFD\x14\xFD\x15\xFD\x16\xFD\x17\xFD\x18\xFD\x19\xFD\x1A\xFD\x1B\xFD\x1C\xFD\x1D\xFD\x1E\xFD\x1F", 32);
    const QByteArray rangeFD2x = QByteArray::fromRawData("\xFD\x20\xFD\x21\xFD\x22\xFD\x23\xFD\x24\xFD\x25\xFD\x26\xFD\x27\xFD\x28\xFD\x29\xFD\x2A\xFD\x2B\xFD\x2C\xFD\x2D\xFD\x2E\xFD\x2F", 32);
    const QByteArray rangeFD3x = QByteArray::fromRawData("\xFD\x30\xFD\x31\xFD\x32\xFD\x33\xFD\x34\xFD\x35\xFD\x36\xFD\x37\xFD\x38\xFD\x39\xFD\x3A\xFD\x3B\xFD\x3C\xFD\x3D\xFD\x3E\xFD\x3F", 32);
    const QByteArray rangeFD4x = QByteArray::fromRawData("\xFD\x40\xFD\x41\xFD\x42\xFD\x43\xFD\x44\xFD\x45\xFD\x46\xFD\x47\xFD\x48\xFD\x49\xFD\x4A\xFD\x4B\xFD\x4C\xFD\x4D\xFD\x4E\xFD\x4F", 32);
    const QByteArray rangeFD5x = QByteArray::fromRawData("\xFD\x50\xFD\x51\xFD\x52\xFD\x53\xFD\x54\xFD\x55\xFD\x56\xFD\x57\xFD\x58\xFD\x59\xFD\x5A\xFD\x5B\xFD\x5C\xFD\x5D\xFD\x5E\xFD\x5F", 32);
    const QByteArray rangeFD6x = QByteArray::fromRawData("\xFD\x60\xFD\x61\xFD\x62\xFD\x63\xFD\x64\xFD\x65\xFD\x66\xFD\x67\xFD\x68\xFD\x69\xFD\x6A\xFD\x6B\xFD\x6C\xFD\x6D\xFD\x6E\xFD\x6F", 32);
    const QByteArray rangeFD7x = QByteArray::fromRawData("\xFD\x70\xFD\x71\xFD\x72\xFD\x73\xFD\x74\xFD\x75\xFD\x76\xFD\x77\xFD\x78\xFD\x79\xFD\x7A\xFD\x7B\xFD\x7C\xFD\x7D\xFD\x7E\xFD\x7F", 32);
    const QByteArray rangeFD8x = QByteArray::fromRawData("\xFD\x80\xFD\x81\xFD\x82\xFD\x83\xFD\x84\xFD\x85\xFD\x86\xFD\x87\xFD\x88\xFD\x89\xFD\x8A\xFD\x8B\xFD\x8C\xFD\x8D\xFD\x8E\xFD\x8F", 32);
    const QByteArray rangeFD9x = QByteArray::fromRawData("\xFD\x90\xFD\x91\xFD\x92\xFD\x93\xFD\x94\xFD\x95\xFD\x96\xFD\x97\xFD\x98\xFD\x99\xFD\x9A\xFD\x9B\xFD\x9C\xFD\x9D\xFD\x9E\xFD\x9F", 32);
    const QByteArray rangeFDAx = QByteArray::fromRawData("\xFD\xA0\xFD\xA1\xFD\xA2\xFD\xA3\xFD\xA4\xFD\xA5\xFD\xA6\xFD\xA7\xFD\xA8\xFD\xA9\xFD\xAA\xFD\xAB\xFD\xAC\xFD\xAD\xFD\xAE\xFD\xAF", 32);
    const QByteArray rangeFDBx = QByteArray::fromRawData("\xFD\xB0\xFD\xB1\xFD\xB2\xFD\xB3\xFD\xB4\xFD\xB5\xFD\xB6\xFD\xB7\xFD\xB8\xFD\xB9\xFD\xBA\xFD\xBB\xFD\xBC\xFD\xBD\xFD\xBE\xFD\xBF", 32);
    const QByteArray rangeFDCx = QByteArray::fromRawData("\xFD\xC0\xFD\xC1\xFD\xC2\xFD\xC3\xFD\xC4\xFD\xC5\xFD\xC6\xFD\xC7\xFD\xC8\xFD\xC9\xFD\xCA\xFD\xCB\xFD\xCC\xFD\xCD\xFD\xCE\xFD\xCF", 32);
    const QByteArray rangeFDDx = QByteArray::fromRawData("\xFD\xD0\xFD\xD1", 4);

    const QString rangeFD0xJ = QStringLiteral("友伝夜探対調民読占頼若学識業歳争");
    const QString rangeFD1xJ = QStringLiteral("苦織困答準恐認客務居他再幸役縮情");
    const QString rangeFD2xJ = QStringLiteral("豊夫近窟責建求迎貸期工算湿難保帯");
    const QString rangeFD3xJ = QStringLiteral("届凝笑向可遊襲申次国素題普密望官");
    const QString rangeFD4xJ = QStringLiteral("泣創術演輝買途浴老幼利門格原管牧");
    const QString rangeFD5xJ = QStringLiteral("炭彼房驚禁注整衆語証深層査渡号科");
    const QString rangeFD6xJ = QStringLiteral("欲店括坑酬緊研権書暇兄派造広川賛");
    const QString rangeFD7xJ = QStringLiteral("駅絡在党岸服捜姉敷胸刑谷痛岩至勢");
    const QString rangeFD8xJ = QStringLiteral("畑姿統略抹展示修酸製歓接障災室索");
    const QString rangeFD9xJ = QStringLiteral("扉傷録優基讐勇司境璧医怖狙協犯資");
    const QString rangeFDAxJ = QStringLiteral("設雇根億脱富躍純写病依到練順園総");
    const QString rangeFDBxJ = QStringLiteral("念維検朽圧補公働因朝浪祝恋郎勉春");
    const QString rangeFDCxJ = QStringLiteral("功耳恵緑美辺昇悩泊低酒影競二矢瞬");
    const QString rangeFDDxJ = QStringLiteral("希志");

    const QByteArray rangeFE0x = QByteArray::fromRawData("\xFE\x00\xFE\x01\xFE\x02\xFE\x03\xFE\x04\xFE\x05\xFE\x06\xFE\x07\xFE\x08\xFE\x09\xFE\x0A\xFE\x0B\xFE\x0C\xFE\x0D\xFE\x0E\xFE\x0F", 32);
    const QByteArray rangeFE1x = QByteArray::fromRawData("\xFE\x10\xFE\x11\xFE\x12\xFE\x13\xFE\x14\xFE\x15\xFE\x16\xFE\x17\xFE\x18\xFE\x19\xFE\x1A\xFE\x1B\xFE\x1C\xFE\x1D\xFE\x1E\xFE\x1F", 32);
    const QByteArray rangeFE2x = QByteArray::fromRawData("\xFE\x20\xFE\x21\xFE\x22\xFE\x23\xFE\x24\xFE\x25\xFE\x26\xFE\x27\xFE\x28\xFE\x29\xFE\x2A\xFE\x2B\xFE\x2C\xFE\x2D\xFE\x2E\xFE\x2F", 32);
    const QByteArray rangeFE3x = QByteArray::fromRawData("\xFE\x30\xFE\x31\xFE\x32\xFE\x33\xFE\x34\xFE\x35\xFE\x36\xFE\x37\xFE\x38\xFE\x39\xFE\x3A\xFE\x3B\xFE\x3C\xFE\x3D\xFE\x3E\xFE\x3F", 32);
    const QByteArray rangeFE4x = QByteArray::fromRawData("\xFE\x40\xFE\x41\xFE\x42\xFE\x43\xFE\x44\xFE\x45\xFE\x46\xFE\x47\xFE\x48\xFE\x49\xFE\x4A\xFE\x4B\xFE\x4C\xFE\x4D\xFE\x4E\xFE\x4F", 32);
    const QByteArray rangeFE5x = QByteArray::fromRawData("\xFE\x50\xFE\x51\xFE\x52\xFE\x53\xFE\x54\xFE\x55\xFE\x56\xFE\x57\xFE\x58\xFE\x59\xFE\x5A\xFE\x5B\xFE\x5C\xFE\x5D\xFE\x5E\xFE\x5F", 32);
    const QByteArray rangeFE6x = QByteArray::fromRawData("\xFE\x60\xFE\x61\xFE\x62\xFE\x63\xFE\x64\xFE\x65\xFE\x66\xFE\x67\xFE\x68\xFE\x69\xFE\x6A\xFE\x6B\xFE\x6C\xFE\x6D\xFE\x6E\xFE\x6F", 32);
    const QByteArray rangeFE7x = QByteArray::fromRawData("\xFE\x70\xFE\x71\xFE\x72\xFE\x73\xFE\x74\xFE\x75\xFE\x76\xFE\x77\xFE\x78\xFE\x79\xFE\x7A\xFE\x7B\xFE\x7C\xFE\x7D\xFE\x7E\xFE\x7F", 32);
    const QByteArray rangeFE8x = QByteArray::fromRawData("\xFE\x80\xFE\x81\xFE\x82\xFE\x83\xFE\x84\xFE\x85\xFE\x86\xFE\x87\xFE\x88\xFE\x89\xFE\x8A\xFE\x8B\xFE\x8C\xFE\x8D\xFE\x8E\xFE\x8F", 32);
    const QByteArray rangeFE9x = QByteArray::fromRawData("\xFE\x90\xFE\x91\xFE\x92\xFE\x93\xFE\x94\xFE\x95\xFE\x96\xFE\x97\xFE\x98\xFE\x99\xFE\x9A\xFE\x9B\xFE\x9C\xFE\x9D\xFE\x9E\xFE\x9F", 32);
    const QByteArray rangeFEAx = QByteArray::fromRawData("\xFE\xA0\xFE\xA1\xFE\xA2\xFE\xA3\xFE\xA4\xFE\xA5\xFE\xA6\xFE\xA7\xFE\xA8\xFE\xA9\xFE\xAA\xFE\xAB\xFE\xAC\xFE\xAD\xFE\xAE\xFE\xAF", 32);
    const QByteArray rangeFEBx = QByteArray::fromRawData("\xFE\xB0\xFE\xB1\xFE\xB2\xFE\xB3\xFE\xB4\xFE\xB5\xFE\xB6\xFE\xB7\xFE\xB8\xFE\xB9\xFE\xBA\xFE\xBB\xFE\xBC\xFE\xBD\xFE\xBE\xFE\xBF", 32);
    const QByteArray rangeFECx = QByteArray::fromRawData("\xFE\xC0\xFE\xC1\xFE\xC2\xFE\xC3\xFE\xC4\xFE\xC5\xFE\xC6\xFE\xC7\xFE\xC8\xFE\xC9\xFE\xCA\xFE\xCB\xFE\xCC\xFE\xCD\xFE\xCE\xFE\xCF", 32);
    const QByteArray rangeFEDx = QByteArray::fromRawData("\xFE\xD0\xFE\xD1\xFE\xD2\xFE\xD3\xFE\xD4\xFE\xD5\xFE\xD6\xFE\xD7\xFE\xD8\xFE\xD9\xFE\xDA\xFE\xDB\xFE\xDC\xFE\xDD\x42\xFE\xDE\xFE\xDF", 33);  // FEDD is Pause%1, May need a more complete test
    const QByteArray rangeFEEx = QByteArray::fromRawData("\xFE\xE0\xFE\xE1\xFE\xE2\x01\x02\x03\x00\xFE\xE9", 12); // FEE2 Memory needs its own Complete Test? FEE3 - FEE8 And FFEA - FFEF are invalid

    const QString rangeFE0xJ = QStringLiteral("孫継団給抗違提断島栄油就僕存企比");
    const QString rangeFE1xJ = QStringLiteral("浸非応細承編排努締談趣埋営文夏個");
    const QString rangeFE2xJ = QStringLiteral("益損額区寒簡遣例肉博幻量昔臓負討");
    const QString rangeFE3xJ = QStringLiteral("悔膨飲妄越憎増枚皆愚療庫涙照冗壇");
    const QString rangeFE4xJ = QStringLiteral("坂訳抱薄義騒奴丈捕被概招劣較析繁");
    const QString rangeFE5xJ = QStringLiteral("殖耐論貴称千歴史募容噂壱胞鳴表雑");
    const QString rangeFE6xJ = QStringLiteral("職妹氏踊停罪甘健焼払侵頃愛便田舎");
    const QString rangeFE7xJ = QStringLiteral("孤晩清際領評課勤謝才偉誤価欠寄忙");
    const QString rangeFE8xJ = QStringLiteral("従五送周頑労植施販台度嫌諸習緒誘");
    const QString rangeFE9xJ = QStringLiteral("仮借輩席戒弟珍酔試騎霜鉱裕票券専");
    const QString rangeFEAxJ = QStringLiteral("祖惰偶怠罰熟牲燃犠快劇拠厄抵適程");
    const QString rangeFEBxJ = QStringLiteral("繰腹橋白処匹杯暑坊週秀看軽幕和平");
    const QString rangeFECxJ = QStringLiteral("王姫庭観航横帳丘亭財律布規謀積刻");
    const QString rangeFEDxJ = QStringLiteral("陥類{GREY}{BLUE}{RED}{PURPLE}{GREEN}{CYAN}{YELLOW}{WHITE}{BLINK}{MULTICOLOUR}{PAUSE}{PAUSE066}{VARDEC}{VARHEX}");
    const QString rangeFEExJ = QStringLiteral("{SCROLLING}{VARDECR}{MEMORY:var[11][1];size=3}{SPACED CHARACTERS}");

    const QByteArray pauseWaitBytes = QByteArray::fromRawData("\xFE\xDD\x42\xFE\xDD\xFF\xFE\xDD\xFE\xFE\xDD\x00\xFE\xDD\x05\xFE\xDD\xDD\xFE\xDD\xED", 21);
    const QString pauseWaitString = QStringLiteral("{PAUSE066}{PAUSE255}{PAUSE254}{PAUSE000}{PAUSE005}{PAUSE221}{PAUSE237}");

    const QByteArray memoryTestBytes = QByteArray::fromRawData("\xFE\xE2\x01\x02\x03\x00\xFE\xE2\x05\x01\x02\x00\xFE\xE2\x05\x03\x02\x00\xFE\xE2\x05\x04\x02\x00\xFE\xE2\x05\x00\x02\x00", 30);
    const QString memoryTestString = QStringLiteral("{MEMORY:var[11][1];size=3}{MEMORY:var[3][5];size=2}{MEMORY:var[13][5];size=2}{MEMORY:var[15][5];size=2}{MEMORY:var[1][5];size=2}");

    const QByteArray memoryErrorBytes = QByteArray::fromRawData("\xFE\xE2\xFF\xFF\xFF\x00\xFE\xE2", 8);
    const QString memoryErrorString = QStringLiteral("{MEMORY:var[0][255];size=255}");
    const QByteArray memoryErrorBytes_Corrected = QByteArray::fromRawData("\xFE\xE2\xFF\x00\xFF\x00", 6);

    const QByteArray TESTBYTES = QByteArray::fromRawData("\xB2\x33\x41\x59\xE2\x41\x52\x45\x4E\x07\x54\x00\x59\x4F\x55\x00\x42\x4F\x52\x45\x44\x1F\xB3\xE7\xE0\x2E\x4F\x54\x00\x54\x48\x41\x54\x00\x4D\x55\x43\x48\xE7\xE0\x39\x45\x41\x48\xE2\x57\x45\x00\x46\x49\x47\x48\x54\x00\x41\x00\x4C\x4F\x54", 59);
    const QString TESTSTRING = QStringLiteral("“Say, aren't you bored?”\n{CHOICE}Not that much\n{CHOICE}Yeah, we fight a lot");

};
