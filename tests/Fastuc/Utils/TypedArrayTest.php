<?hh // strict
namespace Fastuc\Utils;

class TypedArrayNoTest extends \PHPUnit_Framework_TestCase
{
	public function testInitialization()
	{
		$array = new TypedArray;

		$this->assertFalse( $array->hasParam( 'foobar' ) );
		$this->assertNull( $array->getParam( 'foobar' ) );

		$array->setString( 'age', 1 );
		$this->assertSame( '1', $array->getParam( 'age' ) );
	}

	public function testTypes()
	{
		$values = array(
			'name' => 'Daniel',
			'price' => 10.5,
			'age' => 33.2,

			'married' => 1,
			'human' => true,
			'alive' => 'yes',
		);

		$array = new TypedArray( $values );

		$this->assertEquals( 'Daniel', $array->getString( 'name' ) );
		
		$this->assertEquals( 10.5, $array->getFloat( 'price' ) );
		$this->assertEquals( 10, $array->getInt( 'price' ) );

		$this->assertEquals( 33, $array->getInt( 'age' ) );

		$this->assertSame( true, $array->getBoolean( 'married' ) );
		$this->assertSame( true, $array->getBoolean( 'human' ) );
		$this->assertSame( true, $array->getBoolean( 'alive' ) );
	}

	public function testDefaults()
	{
		$array = new TypedArray;

		$this->assertEquals( 'No name', $array->getString( 'name', 'No name' ) );
		
		$this->assertFalse( $array->getBoolean( 'single' ) );
		$this->assertTrue( $array->getBoolean( 'single', true ) );
		
		$this->assertEquals( 5, $array->getInt( 'age', 5 ) );
		$this->assertEquals( 65.34, $array->getFloat( 'weight', 65.34 ) );
	}

	public function testSetUnset()
	{
		$array = new TypedArray;

		$array->setParam( 'foo', 'bar' );
		$this->assertTrue( $array->hasParam( 'foo' ) );

		$array->unsetParam( 'foo' );
		$this->assertFalse( $array->hasParam( 'foo' ) );

		$this->assertEquals( array(), $array->getParams() );
	}

	public function testSetUnsetAll()
	{
		$array = new TypedArray;

		$array->setParam( 'foo', 'bar' );
		$array->setParam( 'boo', 'buu' );

		$this->assertTrue( $array->hasParam( 'foo' ) && $array->hasParam( 'boo' ) );

		$array->unsetParams();
		$this->assertTrue( !$array->hasParam( 'foo' ) && !$array->hasParam( 'boo' ) );
	}
}

