<?hh // strict
namespace Fastuc;

class ClassLoaderTest extends \PHPUnit_Framework_TestCase
{
	public function testNewInstance()
	{
		$classLoader = ClassLoader::getInstance();
		$person1 = $classLoader->newInstance( '\Fastuc\Person_ClassLoaderTest', array( 'Daniel' ) );
		$person2 = $classLoader->newInstance( '\Fastuc\Person_ClassLoaderTest', array( 'Daniel' ) );

		$this->assertEquals( 'Daniel', $person1->getName() );
		$this->assertNotSame( $person1, $person2 );
	}

	public function testNewSingleton()
	{
		$classLoader = ClassLoader::getInstance();
		$person1 = $classLoader->newSingleton( '\Fastuc\Person_ClassLoaderTest', array( 'Scott' ) );
		$person2 = $classLoader->newSingleton( '\Fastuc\Person_ClassLoaderTest', array( 'Tiger' ) );
		$person3 = $classLoader->newSingleton( '\Fastuc\Person_ClassLoaderTest', array( 'Daniel' ) );

		$this->assertSame( $person1, $person2, $person3 );
	}

}

class Person_ClassLoaderTest
{
	private $name;

	public function __construct( $name ) { $this->name = $name; }
	public function getName() { return $this->name; }
}


