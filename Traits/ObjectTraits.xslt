<?xml version="1.0" encoding="utf-8"?>
<?altova_samplexml file:///D:/Projects/dISToBJ/Traits/BaseTypes.xml?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
	<xsl:output method="text"/>
	<xsl:variable name="tab1" select="'&#x9;'"/>
	<xsl:variable name="tab2" select="concat($tab1, '&#x9;')"/>
	<xsl:variable name="tab3" select="concat($tab2, '&#x9;')"/>
	<xsl:variable name="newl1" select="'&#xa;'"/>
	<xsl:variable name="newl2" select="concat($newl1, '&#xa;')"/>
	<!--=======================================================================-->
	<!--header with guards ans includes-->
	<!--=======================================================================-->
	<xsl:template match="/">
		<xsl:variable name="file" select="replace(tokenize(base-uri(.), '/')[last()],'.xml','')"/>
		<xsl:variable name="guard" select="concat($file, 'H')"/>
		<xsl:value-of select="concat('#ifndef ', $guard, $newl1)"/>
		<xsl:value-of select="concat('#define ', $guard, $newl2)"/>
		<xsl:value-of select="concat('#include &quot;Object.h&quot;', $newl1)"/>
		<xsl:value-of select="concat('#include &quot;Traits.h&quot;', $newl2)"/>
		<xsl:value-of select="concat('namespace srdev', $newl1)"/>
		<xsl:value-of select="concat('{', $newl1)"/>

		<xsl:apply-templates select="ObjectTypes/Object" mode="Traits"/>		

		<xsl:value-of select="concat('}', $newl2)"/>
		<xsl:value-of select="concat('#endif', $newl1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Object node-->
	<!--=======================================================================-->
	<xsl:template match="Object" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="id" select="@id"/>
		<xsl:value-of select="concat($tab1, 'namespace ', $category, $newl1)"/>
		<xsl:value-of select="concat($tab1, '{', $newl1)"/>
		<xsl:value-of select="concat($tab2, 'namespace ', $name, $newl1)"/>
		<xsl:value-of select="concat($tab2, '{', $newl1)"/>
		
		<xsl:apply-templates select="Base" mode="Traits"/>

		<xsl:value-of select="concat($tab2, '}', $newl1)"/>
		<xsl:value-of select="concat($tab1, '}', $newl1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process the Base node-->
	<!--=======================================================================-->
	<xsl:template match="Base" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="base" select="concat($category, '::', $name)"/>
		<xsl:value-of select="concat($tab3, 'using BaseTraits = ', $base, ';', $newl1)"/>
	</xsl:template>
</xsl:stylesheet>
