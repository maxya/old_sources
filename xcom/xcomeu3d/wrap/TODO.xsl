<?xml version="1.0" encoding="windows-1251"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html"/>
<xsl:variable name="img-path" select="//@img-path" />


<xsl:template match="/">
<html>
<head>
<title><xsl:value-of select="//summary/title"/></title>
<style>
body	{ font-family: tahoma, vernana, arial; background-color: #E7EFF1; }
h1, h2	{ text-align: center; }
</style>
</head>
<body>
  <xsl:apply-templates select="//summary" />
  <xsl:apply-templates select="//category" />
</body>
</html>
</xsl:template>

<xsl:template match="summary">
  <h1>TODO: <xsl:value-of select="title"/></h1>
  <hr />
</xsl:template>

<xsl:template match="category">
 <h2><xsl:value-of select="@name"/></h2>
 <table width='100%'>
  <thead>
    <th width='30%'>Приоритет</th>
    <th width='96px'>Класс</th>
    <th>Название</th>
    <th width='10%'>Прогресс</th>
  </thead>
  <tbody>
  <xsl:apply-templates select="./todo">
    <xsl:with-param name="category" select="@name"/>
    <xsl:sort select="@progress=1 or @progress='done'" order='ascending'/>
    <xsl:sort select="@progress" order='descending'/>
    <xsl:sort select="@priority" order='descending'/>
  </xsl:apply-templates>
  </tbody>
 </table>
</xsl:template>

<xsl:template match="todo">
  <xsl:param name="category" />
  <xsl:variable name="priority-index" select="1 + round( @priority * (count(//priority) - 1) )" />
  <xsl:variable name="priority-node" select="//priority[$priority-index]" />
  <tr>
    <xsl:element name="td">
      <xsl:attribute name="style"><xsl:value-of select="$priority-node/@style"/></xsl:attribute>
      <xsl:value-of select="$priority-node/@name"/> (<xsl:value-of select="round(@priority*100)" />%)
    </xsl:element>
    <td>
      <xsl:apply-templates select="@class"/>
    </td>
    <td><xsl:value-of select="."/></td>
    <td><xsl:apply-templates select="@progress"/></td>
  </tr>
</xsl:template>

<xsl:template match="todo/@class">
  <xsl:variable name="class" select="." />
  <xsl:for-each select="//class">
    <xsl:if test="contains($class, @name)">
      <xsl:element name="img">
        <xsl:attribute name="src"><xsl:value-of select="$img-path"/>/<xsl:value-of select="@img"/></xsl:attribute>
        <xsl:attribute name="alt"><xsl:value-of select="@desc"/></xsl:attribute>
      </xsl:element>
    </xsl:if>
  </xsl:for-each>
</xsl:template>

<xsl:template match="todo/@progress">
 <table width='200'><tr><td width='132'>
  <table cellSpacing='0' cellPadding='0'><tr>
    <td width='4'>
      <xsl:element name="img">
	<xsl:attribute name="width">4</xsl:attribute>
	<xsl:attribute name="height">16</xsl:attribute>
        <xsl:attribute name="src"><xsl:value-of select="$img-path"/>/progress-beg.png</xsl:attribute>
      </xsl:element>
    </td>
    <td>
      <xsl:element name="img">
	<xsl:attribute name="width"><xsl:value-of select="round(128 * .)" /></xsl:attribute>
	<xsl:attribute name="height">16</xsl:attribute>
        <xsl:attribute name="src"><xsl:value-of select="$img-path"/>/progress-unit.png</xsl:attribute>
      </xsl:element>
    </td>
    <td width='4'>
      <xsl:element name="img">
	<xsl:attribute name="width">4</xsl:attribute>
	<xsl:attribute name="height">16</xsl:attribute>
        <xsl:attribute name="src"><xsl:value-of select="$img-path"/>/progress-end.png</xsl:attribute>
      </xsl:element>
    </td>
    <td> </td>
  </tr></table>
 </td>
 <td><nobr> 
	  <xsl:element name="span">
		<xsl:choose>
		<xsl:when test=".='done' or .=1">
		  <xsl:attribute name="style">font-weight: bold; color: #FF0000</xsl:attribute>
		  <xsl:text>done</xsl:text>
		<xsl:variable name="progress" select="1" />
		</xsl:when>
		<xsl:otherwise>
		  <xsl:attribute name="style">color: #00AF00</xsl:attribute>
		  <xsl:value-of select="round( . * 100)" />%
		</xsl:otherwise>
		</xsl:choose>
	  </xsl:element>
  </nobr></td>
 </tr></table>
  
</xsl:template>

</xsl:stylesheet>

