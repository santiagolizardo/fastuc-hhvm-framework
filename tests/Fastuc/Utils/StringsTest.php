<?hh // strict
namespace Fastuc\Utils;

class StringsTest extends \PHPUnit_Framework_TestCase
{
	public function testTransliteration()
	{
		$result = \Fastuc\Utils\Strings::transliterate( 'µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ' );
		$this->assertEquals( 'uAAAAAAACEEEEIIIIDNOOOOOOUUUUYsaaaaaaaceeeeiiiionoooooouuuuyy', $result );
	}

	public function testCapitalization()
	{
		$this->assertEquals( 'STOP', Strings::capitalizeWords( 'STOP' ) );
		$this->assertEquals( 'Z', Strings::capitalizeWords( 'z' ) );
		$this->assertEquals( 'FooBar', Strings::capitalizeWords( 'fooBar' ) );
		$this->assertEquals( 'View/Test', Strings::capitalizeWords( 'view/test' ) );
	}

	public function dataProviderForCamelCase()
	{
		return array(
			array( 'foo', 'foo' ),
			array( 'FOO', 'foo' ),
			array( 'foo_bar', 'fooBar' ),
			array( 'fOO_BAR_scott', 'fooBarScott' ),
		);
	}

	/**
	 * @dataProvider dataProviderForCamelCase
	 */
	public function testCamelCase( $given, $expected )
	{
		$this->assertEquals( $expected, \Fastuc\Utils\Strings::toCamelCase( $given ) );
	}
}

