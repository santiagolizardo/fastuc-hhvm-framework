<?hh // strict
namespace Fastuc\Input;

class Request extends Http
{
	public function __construct()
	{
		parent::__construct( 'REQUEST' );
	}
}

