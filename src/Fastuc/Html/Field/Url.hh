<?hh // strict
namespace Fastuc\Html\Field;

class Url extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'url', $name, $value );
	}
}

