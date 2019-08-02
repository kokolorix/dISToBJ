<?xml version="1.0" encoding="utf-8"?>
<?altova_samplexml file:///D:/Projects/dISToBJ/Traits/BaseTypes.xml?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
	<xsl:output method="text"/>
	<xsl:variable name="tab1" select="'&#x9;'"/>
	<xsl:variable name="tab2" select="concat($tab1, '&#x9;')"/>
	<xsl:variable name="tab3" select="concat($tab2, '&#x9;')"/>
	<xsl:variable name="tab4" select="concat($tab3, '&#x9;')"/>
	<xsl:variable name="tab5" select="concat($tab4, '&#x9;')"/>
	<xsl:variable name="newLine1" select="'&#xa;'"/>
	<xsl:variable name="newLine2" select="concat($newLine1, '&#xa;')"/>
	<!--=======================================================================-->
	<!--header with guards ans includes -->
	<!--=======================================================================-->
	<xsl:template match="/">
		<xsl:variable name="file" select="replace(tokenize(base-uri(.), '/')[last()],'.xml','')"/>
		<xsl:variable name="guard" select="concat($file, 'H')"/>
		<xsl:value-of select="concat('#ifndef ', $guard, $newLine1)"/>
		<xsl:value-of select="concat('#define ', $guard, $newLine2)"/>
		<xsl:value-of select="concat('#include &quot;Object.h&quot;', $newLine1)"/>
		<xsl:value-of select="concat('#include &quot;Traits.h&quot;', $newLine2)"/>
		<xsl:value-of select="concat('namespace srdev', $newLine1)"/>
		<xsl:value-of select="concat('{', $newLine1)"/>
		<xsl:apply-templates select="ObjectTypes/Object" mode="Traits"/>
		<xsl:value-of select="concat('}', $newLine2)"/>
		<xsl:value-of select="concat('#endif', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Object node -->
	<!--=======================================================================-->
	<xsl:template match="Object" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="id" select="@id"/>
		<xsl:value-of select="concat($tab1, 'namespace ', $category, $newLine1)"/>
		<xsl:value-of select="concat($tab1, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'namespace ', $name, 'T', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '{', $newLine1)"/>
		<xsl:apply-templates select="Base" mode="Traits"/>
		<xsl:apply-templates select="Property" mode="PropertyT"/>
		<xsl:value-of select="concat($tab3, 'struct PropertiesT', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '{', $newLine1)"/>
		<xsl:apply-templates select="Property" mode="using"/>
		<xsl:value-of select="concat($tab4, 'using List = std::tuple&lt;')"/>
		<xsl:apply-templates select="Property" mode="tuple"/>
		<xsl:value-of select="concat('&gt;;', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'enum { LastId = std::tuple_size&lt;List&gt;::value };', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'using ObjectTraits&lt;ObjectT, BaseTraits, PropertiesT&gt;;', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'using ', $name, ' = ', $name, 'T::Traits', $newLine1)"/>
		<xsl:value-of select="concat($tab1, '}', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process the Base node -->
	<!--=======================================================================-->
	<xsl:template match="Base" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="base" select="concat($category, '::', $name)"/>
		<xsl:value-of select="concat($tab3, 'using BaseTraits = ', $base, ';', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for PropertyT -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="PropertyT">
		<xsl:variable name="type" select="@type"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="default" select="@default"/>
		<xsl:value-of select="concat($tab3, 'namespace ', $name, $newLine1)"/>
		<xsl:value-of select="concat($tab3, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'struct PropertyT', $newLine1)"/>
		<xsl:value-of select="concat($tab4, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab5, 'static ', $type, ' getName() { return &quot;', $name, '&quot;; }', $newLine1)"/>
		<xsl:value-of select="concat($tab5, 'static ValuePtr getDefaultValue() { return ', $type, 'Value::make(', $default, '); }', $newLine1)"/>
		<xsl:value-of select="concat($tab4, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '}', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for using -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="using">
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="concat($tab4, 'using ', $name, ' = ', $name, '::Traits;', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for tuple -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="tuple">
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="$name"/>
		<xsl:if test="position() != last()">
			<xsl:text>,</xsl:text>
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>
