//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <ff7tkdata_export.h>
#if QT_VERSION < QT_VERSION_CHECK(6, 5, 0)
#include <QtQml/qqmlapplicationengine.h>
#include <QRegularExpression>
#else
#include <QtQmlIntegration/QtQmlIntegration>
#endif

/*! \class FF7Text
 * \brief Convert ff7text <-> pc string
 */
class FF7TKDATA_EXPORT FF7Text: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(bool japanese READ isJapanese WRITE setJapanese NOTIFY languageChanged)
public:
    /**
     * @brief Get the FF7Text Instance.
     */
    static FF7Text *get();

    /*! \brief sets the text mode, if TRUE will return Japanese text */
    static void setJapanese(bool japanese);

    /*! \brief returns True if using Japanese mode. */
    static bool isJapanese();

    /*! \brief convert ff7text to pc string
     *  \param text the raw ff7text to read
     *  \return decoded ff7text
     */
    static Q_INVOKABLE QString toPC(QByteArray text);

    /*! \brief convert pc string to ff7text
     *  \param string the raw ff7text to read
     *  \return decoded ff7text
     */
    static Q_INVOKABLE QByteArray toFF7(const QString &string);
signals:
    /*! \brief emited when switching language used for decode.
     */
    void languageChanged();
private:
    FF7Text *operator = (FF7Text &other) = delete;
    FF7Text(const FF7Text &other) = delete;
    explicit FF7Text(QObject *parent = nullptr);
    ~FF7Text();
    static QString character(quint8 ord, quint8 table); /** convert a single character*/

    struct FF7TextPrivate{
        bool in_ja = false; /**< if true toPC will give us Japanese characters*/
        inline static const QStringList eng = {
            QStringLiteral(" "), QStringLiteral("!"), QStringLiteral("\""), QStringLiteral("#"), QStringLiteral("$"), QStringLiteral("%"), QStringLiteral("&"), QStringLiteral("'"), QStringLiteral("("), QStringLiteral(")"), QStringLiteral("*"), QStringLiteral("+"), QStringLiteral(","), QStringLiteral("-"), QStringLiteral("."), QStringLiteral("/")
            , QStringLiteral("0"), QStringLiteral("1"), QStringLiteral("2"), QStringLiteral("3"), QStringLiteral("4"), QStringLiteral("5"), QStringLiteral("6"), QStringLiteral("7"), QStringLiteral("8"), QStringLiteral("9"), QStringLiteral(":"), QStringLiteral(";"), QStringLiteral("<"), QStringLiteral("="), QStringLiteral(">"), QStringLiteral("?")
            , QStringLiteral("@"), QStringLiteral("A"), QStringLiteral("B"), QStringLiteral("C"), QStringLiteral("D"), QStringLiteral("E"), QStringLiteral("F"), QStringLiteral("G"), QStringLiteral("H"), QStringLiteral("I"), QStringLiteral("J"), QStringLiteral("K"), QStringLiteral("L"), QStringLiteral("M"), QStringLiteral("N"), QStringLiteral("O")
            , QStringLiteral("P"), QStringLiteral("Q"), QStringLiteral("R"), QStringLiteral("S"), QStringLiteral("T"), QStringLiteral("U"), QStringLiteral("V"), QStringLiteral("W"), QStringLiteral("X"), QStringLiteral("Y"), QStringLiteral("Z"), QStringLiteral("["), QStringLiteral("\\"), QStringLiteral("]"), QStringLiteral("^"), QStringLiteral("_")
            , QStringLiteral("`"), QStringLiteral("a"), QStringLiteral("b"), QStringLiteral("c"), QStringLiteral("d"), QStringLiteral("e"), QStringLiteral("f"), QStringLiteral("g"), QStringLiteral("h"), QStringLiteral("i"), QStringLiteral("j"), QStringLiteral("k"), QStringLiteral("l"), QStringLiteral("m"), QStringLiteral("n"), QStringLiteral("o")
            , QStringLiteral("p"), QStringLiteral("q"), QStringLiteral("r"), QStringLiteral("s"), QStringLiteral("t"), QStringLiteral("u"), QStringLiteral("v"), QStringLiteral("w"), QStringLiteral("x"), QStringLiteral("y"), QStringLiteral("z"), QStringLiteral("{"), QStringLiteral("|"), QStringLiteral("}"), QStringLiteral("~"), QString()
            , QStringLiteral("Ä"), QStringLiteral("Å"), QStringLiteral("Ç"), QStringLiteral("É"), QStringLiteral("Ñ"), QStringLiteral("Ö"), QStringLiteral("Ü"), QStringLiteral("á"), QStringLiteral("à"), QStringLiteral("â"), QStringLiteral("ä"), QStringLiteral("ã"), QStringLiteral("å"), QStringLiteral("ç"), QStringLiteral("é"), QStringLiteral("è")
            , QStringLiteral("ê"), QStringLiteral("ë"), QStringLiteral("í"), QStringLiteral("ì"), QStringLiteral("î"), QStringLiteral("ï"), QStringLiteral("ñ"), QStringLiteral("ó"), QStringLiteral("ò"), QStringLiteral("ô"), QStringLiteral("ö"), QStringLiteral("õ"), QStringLiteral("ú"), QStringLiteral("ù"), QStringLiteral("û"), QStringLiteral("ü")
            , QStringLiteral("⌘"), QStringLiteral("°"), QStringLiteral("¢"), QStringLiteral("£"), QStringLiteral("Ù"), QStringLiteral("Û"), QStringLiteral("¶"), QStringLiteral("ß"), QStringLiteral("®"), QStringLiteral("©"), QStringLiteral("™"), QStringLiteral("´"), QStringLiteral("¨"), QStringLiteral("≠"), QStringLiteral("Æ"), QStringLiteral("Ø")
            , QStringLiteral("∞"), QStringLiteral("±"), QStringLiteral("≤"), QStringLiteral("≥"), QStringLiteral("¥"), QStringLiteral("µ"), QStringLiteral("∂"), QStringLiteral("Σ"), QStringLiteral("Π"), QStringLiteral("π"), QStringLiteral("⌡"), QStringLiteral("ª"), QStringLiteral("º"), QStringLiteral("Ω"), QStringLiteral("æ"), QStringLiteral("ø")
            , QStringLiteral("¿"), QStringLiteral("¡"), QStringLiteral("¬"), QStringLiteral("√"), QStringLiteral("ƒ"), QStringLiteral("≈"), QStringLiteral("∆"), QStringLiteral("«"), QStringLiteral("»"), QStringLiteral("…"), QString(), QStringLiteral("À"), QStringLiteral("Ã"), QStringLiteral("Õ"), QStringLiteral("Œ"), QStringLiteral("œ")
            , QStringLiteral("–"), QStringLiteral("—"), QStringLiteral("“"), QStringLiteral("”"), QStringLiteral("‘"), QStringLiteral("’"), QStringLiteral("÷"), QStringLiteral("◊"), QStringLiteral("ÿ"), QStringLiteral("Ÿ"), QStringLiteral("⁄"), QStringLiteral("¤"), QStringLiteral("‹"), QStringLiteral("›"), QStringLiteral("ﬁ"), QStringLiteral("ﬂ")
            , QStringLiteral("■"), QStringLiteral("▪"), QStringLiteral("‚"), QStringLiteral("„"), QStringLiteral("‰"), QStringLiteral("Â"), QStringLiteral("Ê"), QStringLiteral("Á"), QStringLiteral("Ë"), QStringLiteral("È"), QStringLiteral("Í"), QStringLiteral("Î"), QStringLiteral("Ï"), QStringLiteral("Ì"), QStringLiteral("Ó"), QStringLiteral("Ô")
            , QString(), QStringLiteral("Ò"), QStringLiteral("Ù"), QStringLiteral("Û"), QString(), QString(), QString(), QString(), QString(), QString(), QString(), QString(), QString(), QString(), QString(), QString()
            , QStringLiteral("{CHOICE}"), QStringLiteral("\t"), QStringLiteral(", "), QStringLiteral(".\""), QStringLiteral("…\""), QString(), QString(), QStringLiteral("\n"), QStringLiteral("\n{NEW PAGE}\n"), QStringLiteral("\n{NEW PAGE 2}\n"), QStringLiteral("{CLOUD}"), QStringLiteral("{BARRET}"), QStringLiteral("{TIFA}"), QStringLiteral("{AERITH}"), QStringLiteral("{RED XIII}"), QStringLiteral("{YUFFIE}")
            , QStringLiteral("{CAIT SITH}"), QStringLiteral("{VINCENT}"), QStringLiteral("{CID}"), QStringLiteral("{MEMBER 1}"), QStringLiteral("{MEMBER 2}"), QStringLiteral("{MEMBER 3}"), QStringLiteral("{CIRCLE}"), QStringLiteral("{TRIANGLE}"), QStringLiteral("{SQUARE}"), QStringLiteral("{CROSS}"), QString(), QString(), QString(), QString(), QString(), QString()
        };
        inline static const QStringList jap = {
            QStringLiteral("バ"), QStringLiteral("ば"), QStringLiteral("ビ"), QStringLiteral("び"), QStringLiteral("ブ"), QStringLiteral("ぶ"), QStringLiteral("ベ"), QStringLiteral("べ"), QStringLiteral("ボ"), QStringLiteral("ぼ"), QStringLiteral("ガ"), QStringLiteral("が"), QStringLiteral("ギ"), QStringLiteral("ぎ"), QStringLiteral("グ"), QStringLiteral("ぐ")
            , QStringLiteral("ゲ"), QStringLiteral("げ"), QStringLiteral("ゴ"), QStringLiteral("ご"), QStringLiteral("ザ"), QStringLiteral("ざ"), QStringLiteral("ジ"), QStringLiteral("じ"), QStringLiteral("ズ"), QStringLiteral("ず"), QStringLiteral("ゼ"), QStringLiteral("ぜ"), QStringLiteral("ゾ"), QStringLiteral("ぞ"), QStringLiteral("ダ"), QStringLiteral("だ")
            , QStringLiteral("ヂ"), QStringLiteral("ぢ"), QStringLiteral("ヅ"), QStringLiteral("づ"), QStringLiteral("デ"), QStringLiteral("で"), QStringLiteral("ド"), QStringLiteral("ど"), QStringLiteral("ヴ"), QStringLiteral("パ"), QStringLiteral("ぱ"), QStringLiteral("ピ"), QStringLiteral("ぴ"), QStringLiteral("プ"), QStringLiteral("ぷ"), QStringLiteral("ペ")
            , QStringLiteral("ぺ"), QStringLiteral("ポ"), QStringLiteral("ぽ"), QStringLiteral("０"), QStringLiteral("１"), QStringLiteral("２"), QStringLiteral("３"), QStringLiteral("４"), QStringLiteral("５"), QStringLiteral("６"), QStringLiteral("７"), QStringLiteral("８"), QStringLiteral("９"), QStringLiteral("、"), QStringLiteral("。"), QStringLiteral("　")
            , QStringLiteral("ハ"), QStringLiteral("は"), QStringLiteral("ヒ"), QStringLiteral("ひ"), QStringLiteral("フ"), QStringLiteral("ふ"), QStringLiteral("ヘ"), QStringLiteral("へ"), QStringLiteral("ホ"), QStringLiteral("ほ"), QStringLiteral("カ"), QStringLiteral("か"), QStringLiteral("キ"), QStringLiteral("き"), QStringLiteral("ク"), QStringLiteral("く")
            , QStringLiteral("ケ"), QStringLiteral("け"), QStringLiteral("コ"), QStringLiteral("こ"), QStringLiteral("サ"), QStringLiteral("さ"), QStringLiteral("シ"), QStringLiteral("し"), QStringLiteral("ス"), QStringLiteral("す"), QStringLiteral("セ"), QStringLiteral("せ"), QStringLiteral("ソ"), QStringLiteral("そ"), QStringLiteral("タ"), QStringLiteral("た")
            , QStringLiteral("チ"), QStringLiteral("ち"), QStringLiteral("ツ"), QStringLiteral("つ"), QStringLiteral("テ"), QStringLiteral("て"), QStringLiteral("ト"), QStringLiteral("と"), QStringLiteral("ウ"), QStringLiteral("う"), QStringLiteral("ア"), QStringLiteral("あ"), QStringLiteral("イ"), QStringLiteral("い"), QStringLiteral("エ"), QStringLiteral("え")
            , QStringLiteral("オ"), QStringLiteral("お"), QStringLiteral("ナ"), QStringLiteral("な"), QStringLiteral("ニ"), QStringLiteral("に"), QStringLiteral("ヌ"), QStringLiteral("ぬ"), QStringLiteral("ネ"), QStringLiteral("ね"), QStringLiteral("ノ"), QStringLiteral("の"), QStringLiteral("マ"), QStringLiteral("ま"), QStringLiteral("ミ"), QStringLiteral("み")
            , QStringLiteral("ム"), QStringLiteral("む"), QStringLiteral("メ"), QStringLiteral("め"), QStringLiteral("モ"), QStringLiteral("も"), QStringLiteral("ラ"), QStringLiteral("ら"), QStringLiteral("リ"), QStringLiteral("り"), QStringLiteral("ル"), QStringLiteral("る"), QStringLiteral("レ"), QStringLiteral("れ"), QStringLiteral("ロ"), QStringLiteral("ろ")
            , QStringLiteral("ヤ"), QStringLiteral("や"), QStringLiteral("ユ"), QStringLiteral("ゆ"), QStringLiteral("ヨ"), QStringLiteral("よ"), QStringLiteral("ワ"), QStringLiteral("わ"), QStringLiteral("ン"), QStringLiteral("ん"), QStringLiteral("ヲ"), QStringLiteral("を"), QStringLiteral("ッ"), QStringLiteral("っ"), QStringLiteral("ャ"), QStringLiteral("ゃ")
            , QStringLiteral("ュ"), QStringLiteral("ゅ"), QStringLiteral("ョ"), QStringLiteral("ょ"), QStringLiteral("ァ"), QStringLiteral("ぁ"), QStringLiteral("ィ"), QStringLiteral("ぃ"), QStringLiteral("ゥ"), QStringLiteral("ぅ"), QStringLiteral("ェ"), QStringLiteral("ぇ"), QStringLiteral("ォ"), QStringLiteral("ぉ"), QStringLiteral("！"), QStringLiteral("？")
            , QStringLiteral("『"), QStringLiteral("』"), QStringLiteral("．"), QStringLiteral("＋"), QStringLiteral("Ａ"), QStringLiteral("Ｂ"), QStringLiteral("Ｃ"), QStringLiteral("Ｄ"), QStringLiteral("Ｅ"), QStringLiteral("Ｆ"), QStringLiteral("Ｇ"), QStringLiteral("Ｈ"), QStringLiteral("Ｉ"), QStringLiteral("Ｊ"), QStringLiteral("Ｋ"), QStringLiteral("Ｌ")
            , QStringLiteral("Ｍ"), QStringLiteral("Ｎ"), QStringLiteral("Ｏ"), QStringLiteral("Ｐ"), QStringLiteral("Ｑ"), QStringLiteral("Ｒ"), QStringLiteral("Ｓ"), QStringLiteral("Ｔ"), QStringLiteral("Ｕ"), QStringLiteral("Ｖ"), QStringLiteral("Ｗ"), QStringLiteral("Ｘ"), QStringLiteral("Ｙ"), QStringLiteral("Ｚ"), QStringLiteral("・"), QStringLiteral("＊")
            , QStringLiteral("ー"), QStringLiteral("～"), QStringLiteral("…"), QStringLiteral("％"), QStringLiteral("／"), QStringLiteral("："), QStringLiteral("＆"), QStringLiteral("【"), QStringLiteral("】"), QStringLiteral("♥"), QStringLiteral("→"), QStringLiteral("α"), QStringLiteral("β"), QStringLiteral("「"), QStringLiteral("」"), QStringLiteral("（")
            , QStringLiteral("）"), QStringLiteral("－"), QStringLiteral("＝"), QString(), QString(), QString(), QStringLiteral("⑬"), QStringLiteral("\n"), QStringLiteral("\n{NEW PAGE}\n"), QStringLiteral("\n{NEW PAGE 2}\n"), QStringLiteral("{CLOUD}"), QStringLiteral("{BARRET}"), QStringLiteral("{TIFA}"), QStringLiteral("{AERITH}"), QStringLiteral("{RED XIII}"), QStringLiteral("{YUFFIE}")
            , QStringLiteral("{CAIT SITH}"), QStringLiteral("{VINCENT}"), QStringLiteral("{CID}"), QStringLiteral("{MEMBER 1}"), QStringLiteral("{MEMBER 2}"), QStringLiteral("{MEMBER 3}"), QStringLiteral("{CIRCLE}"), QStringLiteral("{TRIANGLE}"), QStringLiteral("{SQUARE}"), QStringLiteral("{CROSS}"), QString(), QString(), QString(), QString(), QString(), QString()
        };

        inline static const QStringList jap_fa = {
            QStringLiteral("必"), QStringLiteral("殺"), QStringLiteral("技"), QStringLiteral("地"), QStringLiteral("獄"), QStringLiteral("火"), QStringLiteral("炎"), QStringLiteral("裁"), QStringLiteral("雷"), QStringLiteral("大"), QStringLiteral("怒"), QStringLiteral("斬"), QStringLiteral("鉄"), QStringLiteral("剣"), QStringLiteral("槍"), QStringLiteral("海")
            , QStringLiteral("衝"), QStringLiteral("聖"), QStringLiteral("審"), QStringLiteral("判"), QStringLiteral("転"), QStringLiteral("生"), QStringLiteral("改"), QStringLiteral("暗"), QStringLiteral("黒"), QStringLiteral("釜"), QStringLiteral("天"), QStringLiteral("崩"), QStringLiteral("壊"), QStringLiteral("零"), QStringLiteral("式"), QStringLiteral("自")
            , QStringLiteral("爆"), QStringLiteral("使"), QStringLiteral("放"), QStringLiteral("射"), QStringLiteral("臭"), QStringLiteral("息"), QStringLiteral("死"), QStringLiteral("宣"), QStringLiteral("告"), QStringLiteral("凶"), QStringLiteral("破"), QStringLiteral("晄"), QStringLiteral("撃"), QStringLiteral("画"), QStringLiteral("龍"), QStringLiteral("晴")
            , QStringLiteral("点"), QStringLiteral("睛"), QStringLiteral("超"), QStringLiteral("究"), QStringLiteral("武"), QStringLiteral("神"), QStringLiteral("覇"), QStringLiteral("癒"), QStringLiteral("風"), QStringLiteral("邪"), QStringLiteral("気"), QStringLiteral("封"), QStringLiteral("印"), QStringLiteral("吹"), QStringLiteral("烙"), QStringLiteral("星")
            , QStringLiteral("守"), QStringLiteral("護"), QStringLiteral("命"), QStringLiteral("鼓"), QStringLiteral("動"), QStringLiteral("福"), QStringLiteral("音"), QStringLiteral("掌"), QStringLiteral("打"), QStringLiteral("水"), QStringLiteral("面"), QStringLiteral("蹴"), QStringLiteral("乱"), QStringLiteral("闘"), QStringLiteral("合"), QStringLiteral("体")
            , QStringLiteral("疾"), QStringLiteral("迅"), QStringLiteral("明"), QStringLiteral("鏡"), QStringLiteral("止"), QStringLiteral("抜"), QStringLiteral("山"), QStringLiteral("蓋"), QStringLiteral("世"), QStringLiteral("血"), QStringLiteral("祭"), QStringLiteral("鎧"), QStringLiteral("袖"), QStringLiteral("一"), QStringLiteral("触"), QStringLiteral("者")
            , QStringLiteral("滅"), QStringLiteral("森"), QStringLiteral("羅"), QStringLiteral("万"), QStringLiteral("象"), QStringLiteral("装"), QStringLiteral("備"), QStringLiteral("器"), QStringLiteral("攻"), QStringLiteral("魔"), QStringLiteral("法"), QStringLiteral("召"), QStringLiteral("喚"), QStringLiteral("獣"), QStringLiteral("呼"), QStringLiteral("出")
            , QStringLiteral("持"), QStringLiteral("相"), QStringLiteral("手"), QStringLiteral("物"), QStringLiteral("確"), QStringLiteral("率"), QStringLiteral("弱"), QStringLiteral("投"), QStringLiteral("付"), QStringLiteral("与"), QStringLiteral("変"), QStringLiteral("化"), QStringLiteral("片"), QStringLiteral("方"), QStringLiteral("行"), QStringLiteral("決")
            , QStringLiteral("定"), QStringLiteral("分"), QStringLiteral("直"), QStringLiteral("前"), QStringLiteral("真"), QStringLiteral("似"), QStringLiteral("覚"), QStringLiteral("列"), QStringLiteral("後"), QStringLiteral("位"), QStringLiteral("置"), QStringLiteral("防"), QStringLiteral("御"), QStringLiteral("発"), QStringLiteral("回"), QStringLiteral("連")
            , QStringLiteral("続"), QStringLiteral("敵"), QStringLiteral("全"), QStringLiteral("即"), QStringLiteral("効"), QStringLiteral("果"), QStringLiteral("尾"), QStringLiteral("毒"), QStringLiteral("消"), QStringLiteral("金"), QStringLiteral("針"), QStringLiteral("乙"), QStringLiteral("女"), QStringLiteral("興"), QStringLiteral("奮"), QStringLiteral("剤")
            , QStringLiteral("鎮"), QStringLiteral("静"), QStringLiteral("能"), QStringLiteral("薬"), QStringLiteral("英"), QStringLiteral("雄"), QStringLiteral("榴"), QStringLiteral("弾"), QStringLiteral("右"), QStringLiteral("腕"), QStringLiteral("砂"), QStringLiteral("時"), QStringLiteral("計"), QStringLiteral("糸"), QStringLiteral("戦"), QStringLiteral("惑")
            , QStringLiteral("草"), QStringLiteral("牙"), QStringLiteral("南"), QStringLiteral("極"), QStringLiteral("冷"), QStringLiteral("結"), QStringLiteral("晶"), QStringLiteral("電"), QStringLiteral("鳥"), QStringLiteral("角"), QStringLiteral("有"), QStringLiteral("害"), QStringLiteral("質"), QStringLiteral("爪"), QStringLiteral("光"), QStringLiteral("月")
            , QStringLiteral("反"), QStringLiteral("巨"), QStringLiteral("目"), QStringLiteral("砲"), QStringLiteral("重"), QStringLiteral("力"), QStringLiteral("球"), QStringLiteral("空"), QStringLiteral("双"), QStringLiteral("野"), QStringLiteral("菜"), QStringLiteral("実"), QStringLiteral("兵"), QStringLiteral("単"), QStringLiteral("毛"), QStringLiteral("茶")
            , QStringLiteral("色"), QStringLiteral("髪")
        };

        inline static const QStringList jap_fb = {
            QStringLiteral("安"), QStringLiteral("香"), QStringLiteral("花"), QStringLiteral("会"), QStringLiteral("員"), QStringLiteral("蜂"), QStringLiteral("蜜"), QStringLiteral("館"), QStringLiteral("下"), QStringLiteral("着"), QStringLiteral("入"), QStringLiteral("先"), QStringLiteral("不"), QStringLiteral("子"), QStringLiteral("供"), QStringLiteral("屋")
            , QStringLiteral("商"), QStringLiteral("品"), QStringLiteral("景"), QStringLiteral("交"), QStringLiteral("換"), QStringLiteral("階"), QStringLiteral("模"), QStringLiteral("型"), QStringLiteral("部"), QStringLiteral("離"), QStringLiteral("場"), QStringLiteral("所"), QStringLiteral("仲"), QStringLiteral("間"), QStringLiteral("無"), QStringLiteral("制")
            , QStringLiteral("限"), QStringLiteral("殿"), QStringLiteral("様"), QStringLiteral("秘"), QStringLiteral("氷"), QStringLiteral("河"), QStringLiteral("図"), QStringLiteral("何"), QStringLiteral("材"), QStringLiteral("料"), QStringLiteral("雪"), QStringLiteral("上"), QStringLiteral("進"), QStringLiteral("事"), QStringLiteral("古"), QStringLiteral("代")
            , QStringLiteral("種"), QStringLiteral("鍵"), QStringLiteral("娘"), QStringLiteral("紙"), QStringLiteral("町"), QStringLiteral("住"), QStringLiteral("奥"), QStringLiteral("眠"), QStringLiteral("楽"), QStringLiteral("最"), QStringLiteral("初"), QStringLiteral("村"), QStringLiteral("雨"), QStringLiteral("釘"), QStringLiteral("陸"), QStringLiteral("吉")
            , QStringLiteral("揮"), QStringLiteral("叢"), QStringLiteral("雲"), QStringLiteral("軍"), QStringLiteral("異"), QStringLiteral("常"), QStringLiteral("通"), QStringLiteral("威"), QStringLiteral("父"), QStringLiteral("蛇"), QStringLiteral("矛"), QStringLiteral("青"), QStringLiteral("偃"), QStringLiteral("刀"), QStringLiteral("戟"), QStringLiteral("十")
            , QStringLiteral("字"), QStringLiteral("裏"), QStringLiteral("車"), QStringLiteral("円"), QStringLiteral("輪"), QStringLiteral("卍"), QStringLiteral("折"), QStringLiteral("鶴"), QStringLiteral("倶"), QStringLiteral("戴"), QStringLiteral("螺"), QStringLiteral("貝"), QStringLiteral("突"), QStringLiteral("銀"), QStringLiteral("玉"), QStringLiteral("正")
            , QStringLiteral("宗"), QStringLiteral("具"), QStringLiteral("甲"), QStringLiteral("烈"), QStringLiteral("属"), QStringLiteral("性"), QStringLiteral("吸"), QStringLiteral("収"), QStringLiteral("半"), QStringLiteral("減"), QStringLiteral("土"), QStringLiteral("高"), QStringLiteral("級"), QStringLiteral("状"), QStringLiteral("態"), QStringLiteral("縁")
            , QStringLiteral("闇"), QStringLiteral("睡"), QStringLiteral("石"), QStringLiteral("徐"), QStringLiteral("々"), QStringLiteral("的"), QStringLiteral("指"), QStringLiteral("混"), QStringLiteral("呪"), QStringLiteral("開"), QStringLiteral("始"), QStringLiteral("歩"), QStringLiteral("復"), QStringLiteral("盗"), QStringLiteral("小"), QStringLiteral("治")
            , QStringLiteral("理"), QStringLiteral("同"), QStringLiteral("速"), QStringLiteral("遅"), QStringLiteral("逃"), QStringLiteral("去"), QStringLiteral("視"), QStringLiteral("複"), QStringLiteral("味"), QStringLiteral("沈"), QStringLiteral("黙"), QStringLiteral("還"), QStringLiteral("倍"), QStringLiteral("数"), QStringLiteral("瀕"), QStringLiteral("取")
            , QStringLiteral("返"), QStringLiteral("人"), QStringLiteral("今"), QStringLiteral("差"), QStringLiteral("誰"), QStringLiteral("当"), QStringLiteral("拡"), QStringLiteral("散"), QStringLiteral("飛"), QStringLiteral("以"), QStringLiteral("外"), QStringLiteral("暴"), QStringLiteral("避"), QStringLiteral("振"), QStringLiteral("身"), QStringLiteral("中")
            , QStringLiteral("旋"), QStringLiteral("津"), QStringLiteral("波"), QStringLiteral("育"), QStringLiteral("機"), QStringLiteral("械"), QStringLiteral("擲"), QStringLiteral("炉"), QStringLiteral("新"), QStringLiteral("両"), QStringLiteral("本"), QStringLiteral("君"), QStringLiteral("洞"), QStringLiteral("内"), QStringLiteral("作"), QStringLiteral("警")
            , QStringLiteral("特"), QStringLiteral("殊"), QStringLiteral("板"), QStringLiteral("強"), QStringLiteral("穴"), QStringLiteral("隊"), QStringLiteral("族"), QStringLiteral("亡"), QStringLiteral("霊"), QStringLiteral("鎖"), QStringLiteral("足"), QStringLiteral("刃"), QStringLiteral("頭"), QStringLiteral("怪"), QStringLiteral("奇"), QStringLiteral("虫")
            , QStringLiteral("跳"), QStringLiteral("侍"), QStringLiteral("左"), QStringLiteral("首"), QStringLiteral("潜"), QStringLiteral("長"), QStringLiteral("親"), QStringLiteral("衛"), QStringLiteral("塔"), QStringLiteral("宝"), QStringLiteral("条"), QStringLiteral("像"), QStringLiteral("忍"), QStringLiteral("謎"), QStringLiteral("般"), QStringLiteral("見")
            , QStringLiteral("報"), QStringLiteral("充"), QStringLiteral("填"), QStringLiteral("完"), QStringLiteral("了"), QStringLiteral("銃"), QStringLiteral("元"), QStringLiteral("経"), QStringLiteral("験"), QStringLiteral("値"), QStringLiteral("終"), QStringLiteral("獲"), QStringLiteral("得"), QStringLiteral("名"), QStringLiteral("悲"), QStringLiteral("蛙")
            , QStringLiteral("操"), QStringLiteral("成"), QStringLiteral("費"), QStringLiteral("背"), QStringLiteral("切"), QStringLiteral("替"), QStringLiteral("割")
        };

        inline static const QStringList jap_fc = {
            QStringLiteral("由"), QStringLiteral("閉"), QStringLiteral("記"), QStringLiteral("憶"), QStringLiteral("選"), QStringLiteral("番"), QStringLiteral("街"), QStringLiteral("底"), QStringLiteral("忘"), QStringLiteral("都"), QStringLiteral("過"), QStringLiteral("艇"), QStringLiteral("路"), QStringLiteral("運"), QStringLiteral("搬"), QStringLiteral("船")
            , QStringLiteral("墓"), QStringLiteral("心"), QStringLiteral("港"), QStringLiteral("末"), QStringLiteral("宿"), QStringLiteral("西"), QStringLiteral("道"), QStringLiteral("艦"), QStringLiteral("家"), QStringLiteral("乗"), QStringLiteral("竜"), QStringLiteral("巻"), QStringLiteral("迷"), QStringLiteral("宮"), QStringLiteral("絶"), QStringLiteral("壁")
            , QStringLiteral("支"), QStringLiteral("社"), QStringLiteral("久"), QStringLiteral("件"), QStringLiteral("想"), QStringLiteral("秒"), QStringLiteral("予"), QStringLiteral("多"), QStringLiteral("落"), QStringLiteral("受"), QStringLiteral("組"), QStringLiteral("余"), QStringLiteral("系"), QStringLiteral("標"), QStringLiteral("起"), QStringLiteral("迫")
            , QStringLiteral("日"), QStringLiteral("勝"), QStringLiteral("形"), QStringLiteral("引"), QStringLiteral("現"), QStringLiteral("解"), QStringLiteral("除"), QStringLiteral("磁"), QStringLiteral("互"), QStringLiteral("口"), QStringLiteral("廃"), QStringLiteral("棄"), QStringLiteral("汚"), QStringLiteral("染"), QStringLiteral("液"), QStringLiteral("活")
            , QStringLiteral("令"), QStringLiteral("副"), QStringLiteral("隠"), QStringLiteral("主"), QStringLiteral("斉"), QStringLiteral("登"), QStringLiteral("温"), QStringLiteral("泉"), QStringLiteral("百"), QStringLiteral("段"), QStringLiteral("熱"), QStringLiteral("走"), QStringLiteral("急"), QStringLiteral("降"), QStringLiteral("奪"), QStringLiteral("響")
            , QStringLiteral("嵐"), QStringLiteral("移"), QStringLiteral("危"), QStringLiteral("戻"), QStringLiteral("遠"), QStringLiteral("吠"), QStringLiteral("軟"), QStringLiteral("骨"), QStringLiteral("言"), QStringLiteral("葉"), QStringLiteral("震"), QStringLiteral("叫"), QStringLiteral("噴"), QStringLiteral("舞"), QStringLiteral("狩"), QStringLiteral("粉")
            , QStringLiteral("失"), QStringLiteral("敗"), QStringLiteral("眼"), QStringLiteral("激"), QStringLiteral("盤"), QStringLiteral("逆"), QStringLiteral("鱗"), QStringLiteral("踏"), QStringLiteral("喰"), QStringLiteral("盾"), QStringLiteral("叩"), QStringLiteral("食"), QStringLiteral("凍"), QStringLiteral("退"), QStringLiteral("木"), QStringLiteral("吐")
            , QStringLiteral("線"), QStringLiteral("魅"), QStringLiteral("押"), QStringLiteral("潰"), QStringLiteral("曲"), QStringLiteral("翼"), QStringLiteral("教"), QStringLiteral("皇"), QStringLiteral("太"), QStringLiteral("陽"), QStringLiteral("界"), QStringLiteral("案"), QStringLiteral("挑"), QStringLiteral("援"), QStringLiteral("赤"), QStringLiteral("往")
            , QStringLiteral("殴"), QStringLiteral("意"), QStringLiteral("東"), QStringLiteral("北"), QStringLiteral("参"), QStringLiteral("知"), QStringLiteral("聞"), QStringLiteral("来"), QStringLiteral("仕"), QStringLiteral("別"), QStringLiteral("集"), QStringLiteral("信"), QStringLiteral("用"), QStringLiteral("思"), QStringLiteral("毎"), QStringLiteral("悪")
            , QStringLiteral("枯"), QStringLiteral("考"), QStringLiteral("然"), QStringLiteral("張"), QStringLiteral("好"), QStringLiteral("伍"), QStringLiteral("早"), QStringLiteral("各"), QStringLiteral("独"), QStringLiteral("配"), QStringLiteral("腐"), QStringLiteral("話"), QStringLiteral("帰"), QStringLiteral("永"), QStringLiteral("救"), QStringLiteral("感")
            , QStringLiteral("故"), QStringLiteral("売"), QStringLiteral("浮"), QStringLiteral("市"), QStringLiteral("加"), QStringLiteral("流"), QStringLiteral("約"), QStringLiteral("宇"), QStringLiteral("礼"), QStringLiteral("束"), QStringLiteral("母"), QStringLiteral("男"), QStringLiteral("年"), QStringLiteral("待"), QStringLiteral("宙"), QStringLiteral("立")
            , QStringLiteral("残"), QStringLiteral("俺"), QStringLiteral("少"), QStringLiteral("精"), QStringLiteral("士"), QStringLiteral("私"), QStringLiteral("険"), QStringLiteral("関"), QStringLiteral("倒"), QStringLiteral("休"), QStringLiteral("我"), QStringLiteral("許"), QStringLiteral("郷"), QStringLiteral("助"), QStringLiteral("要"), QStringLiteral("問")
            , QStringLiteral("係"), QStringLiteral("旧"), QStringLiteral("固"), QStringLiteral("荒"), QStringLiteral("稼"), QStringLiteral("良"), QStringLiteral("議"), QStringLiteral("導"), QStringLiteral("夢"), QStringLiteral("追"), QStringLiteral("説"), QStringLiteral("声"), QStringLiteral("任"), QStringLiteral("柱"), QStringLiteral("満"), QStringLiteral("未")
            , QStringLiteral("顔"), QStringLiteral("旅")
        };

        inline static const QStringList jap_fd = {
            QStringLiteral("友"), QStringLiteral("伝"), QStringLiteral("夜"), QStringLiteral("探"), QStringLiteral("対"), QStringLiteral("調"), QStringLiteral("民"), QStringLiteral("読"), QStringLiteral("占"), QStringLiteral("頼"), QStringLiteral("若"), QStringLiteral("学"), QStringLiteral("識"), QStringLiteral("業"), QStringLiteral("歳"), QStringLiteral("争")
            , QStringLiteral("苦"), QStringLiteral("織"), QStringLiteral("困"), QStringLiteral("答"), QStringLiteral("準"), QStringLiteral("恐"), QStringLiteral("認"), QStringLiteral("客"), QStringLiteral("務"), QStringLiteral("居"), QStringLiteral("他"), QStringLiteral("再"), QStringLiteral("幸"), QStringLiteral("役"), QStringLiteral("縮"), QStringLiteral("情")
            , QStringLiteral("豊"), QStringLiteral("夫"), QStringLiteral("近"), QStringLiteral("窟"), QStringLiteral("責"), QStringLiteral("建"), QStringLiteral("求"), QStringLiteral("迎"), QStringLiteral("貸"), QStringLiteral("期"), QStringLiteral("工"), QStringLiteral("算"), QStringLiteral("湿"), QStringLiteral("難"), QStringLiteral("保"), QStringLiteral("帯")
            , QStringLiteral("届"), QStringLiteral("凝"), QStringLiteral("笑"), QStringLiteral("向"), QStringLiteral("可"), QStringLiteral("遊"), QStringLiteral("襲"), QStringLiteral("申"), QStringLiteral("次"), QStringLiteral("国"), QStringLiteral("素"), QStringLiteral("題"), QStringLiteral("普"), QStringLiteral("密"), QStringLiteral("望"), QStringLiteral("官")
            , QStringLiteral("泣"), QStringLiteral("創"), QStringLiteral("術"), QStringLiteral("演"), QStringLiteral("輝"), QStringLiteral("買"), QStringLiteral("途"), QStringLiteral("浴"), QStringLiteral("老"), QStringLiteral("幼"), QStringLiteral("利"), QStringLiteral("門"), QStringLiteral("格"), QStringLiteral("原"), QStringLiteral("管"), QStringLiteral("牧")
            , QStringLiteral("炭"), QStringLiteral("彼"), QStringLiteral("房"), QStringLiteral("驚"), QStringLiteral("禁"), QStringLiteral("注"), QStringLiteral("整"), QStringLiteral("衆"), QStringLiteral("語"), QStringLiteral("証"), QStringLiteral("深"), QStringLiteral("層"), QStringLiteral("査"), QStringLiteral("渡"), QStringLiteral("号"), QStringLiteral("科")
            , QStringLiteral("欲"), QStringLiteral("店"), QStringLiteral("括"), QStringLiteral("坑"), QStringLiteral("酬"), QStringLiteral("緊"), QStringLiteral("研"), QStringLiteral("権"), QStringLiteral("書"), QStringLiteral("暇"), QStringLiteral("兄"), QStringLiteral("派"), QStringLiteral("造"), QStringLiteral("広"), QStringLiteral("川"), QStringLiteral("賛")
            , QStringLiteral("駅"), QStringLiteral("絡"), QStringLiteral("在"), QStringLiteral("党"), QStringLiteral("岸"), QStringLiteral("服"), QStringLiteral("捜"), QStringLiteral("姉"), QStringLiteral("敷"), QStringLiteral("胸"), QStringLiteral("刑"), QStringLiteral("谷"), QStringLiteral("痛"), QStringLiteral("岩"), QStringLiteral("至"), QStringLiteral("勢")
            , QStringLiteral("畑"), QStringLiteral("姿"), QStringLiteral("統"), QStringLiteral("略"), QStringLiteral("抹"), QStringLiteral("展"), QStringLiteral("示"), QStringLiteral("修"), QStringLiteral("酸"), QStringLiteral("製"), QStringLiteral("歓"), QStringLiteral("接"), QStringLiteral("障"), QStringLiteral("災"), QStringLiteral("室"), QStringLiteral("索")
            , QStringLiteral("扉"), QStringLiteral("傷"), QStringLiteral("録"), QStringLiteral("優"), QStringLiteral("基"), QStringLiteral("讐"), QStringLiteral("勇"), QStringLiteral("司"), QStringLiteral("境"), QStringLiteral("璧"), QStringLiteral("医"), QStringLiteral("怖"), QStringLiteral("狙"), QStringLiteral("協"), QStringLiteral("犯"), QStringLiteral("資")
            , QStringLiteral("設"), QStringLiteral("雇"), QStringLiteral("根"), QStringLiteral("億"), QStringLiteral("脱"), QStringLiteral("富"), QStringLiteral("躍"), QStringLiteral("純"), QStringLiteral("写"), QStringLiteral("病"), QStringLiteral("依"), QStringLiteral("到"), QStringLiteral("練"), QStringLiteral("順"), QStringLiteral("園"), QStringLiteral("総")
            , QStringLiteral("念"), QStringLiteral("維"), QStringLiteral("検"), QStringLiteral("朽"), QStringLiteral("圧"), QStringLiteral("補"), QStringLiteral("公"), QStringLiteral("働"), QStringLiteral("因"), QStringLiteral("朝"), QStringLiteral("浪"), QStringLiteral("祝"), QStringLiteral("恋"), QStringLiteral("郎"), QStringLiteral("勉"), QStringLiteral("春")
            , QStringLiteral("功"), QStringLiteral("耳"), QStringLiteral("恵"), QStringLiteral("緑"), QStringLiteral("美"), QStringLiteral("辺"), QStringLiteral("昇"), QStringLiteral("悩"), QStringLiteral("泊"), QStringLiteral("低"), QStringLiteral("酒"), QStringLiteral("影"), QStringLiteral("競"), QStringLiteral("二"), QStringLiteral("矢"), QStringLiteral("瞬")
            , QStringLiteral("希"), QStringLiteral("志")
        };

        inline static const QStringList jap_fe = {
            QStringLiteral("孫"), QStringLiteral("継"), QStringLiteral("団"), QStringLiteral("給"), QStringLiteral("抗"), QStringLiteral("違"), QStringLiteral("提"), QStringLiteral("断"), QStringLiteral("島"), QStringLiteral("栄"), QStringLiteral("油"), QStringLiteral("就"), QStringLiteral("僕"), QStringLiteral("存"), QStringLiteral("企"), QStringLiteral("比")
            , QStringLiteral("浸"), QStringLiteral("非"), QStringLiteral("応"), QStringLiteral("細"), QStringLiteral("承"), QStringLiteral("編"), QStringLiteral("排"), QStringLiteral("努"), QStringLiteral("締"), QStringLiteral("談"), QStringLiteral("趣"), QStringLiteral("埋"), QStringLiteral("営"), QStringLiteral("文"), QStringLiteral("夏"), QStringLiteral("個")
            , QStringLiteral("益"), QStringLiteral("損"), QStringLiteral("額"), QStringLiteral("区"), QStringLiteral("寒"), QStringLiteral("簡"), QStringLiteral("遣"), QStringLiteral("例"), QStringLiteral("肉"), QStringLiteral("博"), QStringLiteral("幻"), QStringLiteral("量"), QStringLiteral("昔"), QStringLiteral("臓"), QStringLiteral("負"), QStringLiteral("討")
            , QStringLiteral("悔"), QStringLiteral("膨"), QStringLiteral("飲"), QStringLiteral("妄"), QStringLiteral("越"), QStringLiteral("憎"), QStringLiteral("増"), QStringLiteral("枚"), QStringLiteral("皆"), QStringLiteral("愚"), QStringLiteral("療"), QStringLiteral("庫"), QStringLiteral("涙"), QStringLiteral("照"), QStringLiteral("冗"), QStringLiteral("壇")
            , QStringLiteral("坂"), QStringLiteral("訳"), QStringLiteral("抱"), QStringLiteral("薄"), QStringLiteral("義"), QStringLiteral("騒"), QStringLiteral("奴"), QStringLiteral("丈"), QStringLiteral("捕"), QStringLiteral("被"), QStringLiteral("概"), QStringLiteral("招"), QStringLiteral("劣"), QStringLiteral("較"), QStringLiteral("析"), QStringLiteral("繁")
            , QStringLiteral("殖"), QStringLiteral("耐"), QStringLiteral("論"), QStringLiteral("貴"), QStringLiteral("称"), QStringLiteral("千"), QStringLiteral("歴"), QStringLiteral("史"), QStringLiteral("募"), QStringLiteral("容"), QStringLiteral("噂"), QStringLiteral("壱"), QStringLiteral("胞"), QStringLiteral("鳴"), QStringLiteral("表"), QStringLiteral("雑")
            , QStringLiteral("職"), QStringLiteral("妹"), QStringLiteral("氏"), QStringLiteral("踊"), QStringLiteral("停"), QStringLiteral("罪"), QStringLiteral("甘"), QStringLiteral("健"), QStringLiteral("焼"), QStringLiteral("払"), QStringLiteral("侵"), QStringLiteral("頃"), QStringLiteral("愛"), QStringLiteral("便"), QStringLiteral("田"), QStringLiteral("舎")
            , QStringLiteral("孤"), QStringLiteral("晩"), QStringLiteral("清"), QStringLiteral("際"), QStringLiteral("領"), QStringLiteral("評"), QStringLiteral("課"), QStringLiteral("勤"), QStringLiteral("謝"), QStringLiteral("才"), QStringLiteral("偉"), QStringLiteral("誤"), QStringLiteral("価"), QStringLiteral("欠"), QStringLiteral("寄"), QStringLiteral("忙")
            , QStringLiteral("従"), QStringLiteral("五"), QStringLiteral("送"), QStringLiteral("周"), QStringLiteral("頑"), QStringLiteral("労"), QStringLiteral("植"), QStringLiteral("施"), QStringLiteral("販"), QStringLiteral("台"), QStringLiteral("度"), QStringLiteral("嫌"), QStringLiteral("諸"), QStringLiteral("習"), QStringLiteral("緒"), QStringLiteral("誘")
            , QStringLiteral("仮"), QStringLiteral("借"), QStringLiteral("輩"), QStringLiteral("席"), QStringLiteral("戒"), QStringLiteral("弟"), QStringLiteral("珍"), QStringLiteral("酔"), QStringLiteral("試"), QStringLiteral("騎"), QStringLiteral("霜"), QStringLiteral("鉱"), QStringLiteral("裕"), QStringLiteral("票"), QStringLiteral("券"), QStringLiteral("専")
            , QStringLiteral("祖"), QStringLiteral("惰"), QStringLiteral("偶"), QStringLiteral("怠"), QStringLiteral("罰"), QStringLiteral("熟"), QStringLiteral("牲"), QStringLiteral("燃"), QStringLiteral("犠"), QStringLiteral("快"), QStringLiteral("劇"), QStringLiteral("拠"), QStringLiteral("厄"), QStringLiteral("抵"), QStringLiteral("適"), QStringLiteral("程")
            , QStringLiteral("繰"), QStringLiteral("腹"), QStringLiteral("橋"), QStringLiteral("白"), QStringLiteral("処"), QStringLiteral("匹"), QStringLiteral("杯"), QStringLiteral("暑"), QStringLiteral("坊"), QStringLiteral("週"), QStringLiteral("秀"), QStringLiteral("看"), QStringLiteral("軽"), QStringLiteral("幕"), QStringLiteral("和"), QStringLiteral("平")
            , QStringLiteral("王"), QStringLiteral("姫"), QStringLiteral("庭"), QStringLiteral("観"), QStringLiteral("航"), QStringLiteral("横"), QStringLiteral("帳"), QStringLiteral("丘"), QStringLiteral("亭"), QStringLiteral("財"), QStringLiteral("律"), QStringLiteral("布"), QStringLiteral("規"), QStringLiteral("謀"), QStringLiteral("積"), QStringLiteral("刻")
            , QStringLiteral("陥"), QStringLiteral("類"), QStringLiteral("{GREY}"), QStringLiteral("{BLUE}"), QStringLiteral("{RED}"), QStringLiteral("{PURPLE}"), QStringLiteral("{GREEN}"), QStringLiteral("{CYAN}"), QStringLiteral("{YELLOW}"), QStringLiteral("{WHITE}"), QStringLiteral("{BLINK}"), QStringLiteral("{MULTICOLOUR}"), QStringLiteral("{PAUSE}"), QString(), QStringLiteral("{VARDEC}"), QStringLiteral("{VARHEX}")
            , QStringLiteral("{SCROLLING}"), QStringLiteral("{VARDECR}"), QString(/*{MEMORY}*/), QString(), QString(), QString(), QString(), QString(), QString(), QStringLiteral("{SPACED CHARACTERS}")
        };

        inline static const QStringList specialChars = {
            QStringLiteral("{CHOICE}")
            , QStringLiteral("\n{NEW PAGE}\n")
            , QStringLiteral("\n{NEW PAGE 2}\n")
            , QStringLiteral("{CLOUD}")
            , QStringLiteral("{BARRET}")
            , QStringLiteral("{TIFA}")
            , QStringLiteral("{AERITH}")
            , QStringLiteral("{RED XIII}")
            , QStringLiteral("{YUFFIE}")
            , QStringLiteral("{CAIT SITH}")
            , QStringLiteral("{VINCENT}")
            , QStringLiteral("{CID}")
            , QStringLiteral("{MEMBER 1}")
            , QStringLiteral("{MEMBER 2}")
            , QStringLiteral("{MEMBER 3}")
            , QStringLiteral("{CIRCLE}")
            , QStringLiteral("{TRIANGLE}")
            , QStringLiteral("{SQUARE}")
            , QStringLiteral("{CROSS}")
            , QStringLiteral(", ")
            , QStringLiteral(".\"")
            , QStringLiteral("…\"")
            , QStringLiteral("{GREY}")
            , QStringLiteral("{BLUE}")
            , QStringLiteral("{RED}")
            , QStringLiteral("{PURPLE}")
            , QStringLiteral("{GREEN}")
            , QStringLiteral("{CYAN}")
            , QStringLiteral("{YELLOW}")
            , QStringLiteral("{WHITE}")
            , QStringLiteral("{BLINK}")
            , QStringLiteral("{MULTICOLOUR}")
            , QStringLiteral("{PAUSE}")
            , QStringLiteral("{VARDEC}")
            , QStringLiteral("{VARHEX}")
            , QStringLiteral("{SCROLLING}")
            , QStringLiteral("{VARDECR}")
            , QStringLiteral("{SPACED CHARACTERS}")
        };
        QRegularExpression pauseEXP = QRegularExpression(QStringLiteral("{PAUSE\\d{3}}"), QRegularExpression::CaseInsensitiveOption);
        QRegularExpression memoryEXP = QRegularExpression(QStringLiteral("^{MEMORY:var\\[(\\d+)\\]\\[(\\d+)\\];size=(\\d+)}"), QRegularExpression::CaseInsensitiveOption);
    };
    FF7TextPrivate *d;
};
