<?hh // strict
namespace Fastuc\Services;

class GravatarTest extends \PHPUnit_Framework_TestCase
{
	public function testEmailOnly()
	{
		$email = 'foo@bar.on';
		$imageUrl = sprintf( 'http://www.gravatar.com/avatar/%s.jpg?s=80', md5( strtolower( $email ) ) );

		$this->assertEquals( $imageUrl, Gravatar::createImageUrl( $email ) );
	}

	public function testEmailSizeAndFallbackImage()
	{
		$inputServer = new \Fastuc\Input\Server;
		$inputServer->setParam( 'HTTP_HOST', 'fastuc.org' );

		$email = 'foo@bar.on';
		$imageUrl = sprintf( 'http://www.gravatar.com/avatar/%s.jpg?s=120&d=http%%3A%%2F%%2Ffastuc.org%%2Fsmile.png', md5( strtolower( $email ) ) );

		$this->assertEquals( $imageUrl, Gravatar::createImageUrl( $email, 120, '/smile.png' ) );
	}
}

