<?hh // strict
namespace Fastuc\Input;

class HandlerText extends \PHPUnit_Framework_TestCase
{
	public function dataProviderForGeneral()
	{
		return array
		(
			array(
				null,
				'',
				array( 'empty' => false ),
				array(),
			),
			array(
				'country',
				'   COUNTRY  ',
				array(),
				array( 'trim', 'lowercase' ),
			),
			array(
				'i would like to be a hacker',
				'i would <strong>like</strong> to be a <script>hacker</script>',
				array(),
				array( 'striptags' ),
			),

			array(
				null,
				'(34) 123456',
				array( 'regex' => '/^\+\d+ \d+$/' ),
				array(),
			),
			array(
				'+34 123456',
				'+34 123456',
				array( 'regex' => '/^\+\d+ \d+$/' ),
				array(),
			),
			array(
				'user-name',
				'User Name',
				array( 'empty' => false ),
				array( 'lowercase', 'sanitize' ),
			),
			array(
				null,
				'30',
				array( 'max-value' => 20 ),
				array(),
			),
			array(
				'LONG DESC',
				'Long Description',
				array( 'empty' => false ),
				array( 'truncate' => 9, 'uppercase' ),
			),
			array(
				null,
				'rootatlocalhost',
				array( 'email' ),
				array(),
			),
			array(
				'root@inetaddr.es',
				'root@inetaddr.es',
				array( 'email' ),
				array(),
			),
			array(
				'canco',
				'Cançó',
				array(),
				array( 'lowercase', 'transliterate' ),
			),

		);
	}

	/**
	 * @dataProvider dataProviderForGeneral
	 */
	public function testGeneral( $expected, $input, $validations, $transformations )
	{
		$handler = new Handler;
		$this->assertSame( $expected, $handler->getValue( $input, $validations, null, $transformations ) );
	}

	/**
	 * @expectedException \PHPUnit_Framework_Error
	 * @expectedExceptionMessage Validation does not exist: fake
	 */
	public function testInvalidValidation()
	{
		$handler = new Handler;
		$handler->getValue( 'foobarbaz', array( 'fake' ) );
	}

}

