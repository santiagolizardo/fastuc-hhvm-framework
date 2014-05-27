<?hh // strict
namespace Fastuc\Exception;

class MissingExtension extends \Exception
{
	/**
	 * @param string $name
	 */
	public function __construct( string $name )
	{
		parent::__construct( "The extension \"$name\" is not installed" );
	}
}

